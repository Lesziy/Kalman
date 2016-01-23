#include <mutex>
#include <functional>
#include <deque>
#include <boost/signals2.hpp>
#include <type_traits>
#include <condition_variable>
#include "Status.h"
#include "Workable.h"

namespace CommonUtil {
	/** @brief Typ wykorzystywany jako symboliczna odmiana typu void.

		Ciekawostka: typ void nie może być stosowany jako argument via typedef
		w GCC.
	*/
	//typdef int int;

	//! Zbiór trejtów wykorzystywanych w CommonUtil::Worker
	namespace Traits {

		//! Trejt uoogólniający cechę przesyłania danych.
		struct ThreadProcSendable
		{
			//! Typ jaki Worker::ThreadProc zwraca.
			typedef Status ThreadProcType;

			//! Argument funkcji Worker::ThreadProc
			typedef int ThreadProcArg;

			/** @brief Typ który jest odpowiedzialny za obsługę przesyłania wiadomości.

				\sa Worker, szczególnie operator()()
			*/
			typedef boost::signals2::signal<void(Status)> SignalType;

			/** @brief Typ kolejki w Worker.

				Ze względu na ogólność i multiplatformowość projektu typ musi
				mieć jakąś postać nawet w ThreadProcSendable zjadliwą dla
				kompilatora.
				\sa int
			*/
			typedef int QueueType;
		};

		//! Trejt który określa moduły tylko nadające informację(np. Generator)
		struct OutputWorker : public ThreadProcSendable { };
		//! Trejt który określa moduły jedynie przyjmujące dane.(np. Writer)
		struct InputWorker
		{
			//! @copydoc CommonUtil::Traits::ThreadProcSendable::ThreadProcType
			typedef int ThreadProcType;
			//! @copydoc CommonUtil::Traits::ThreadProcSendable::ThreadProcArg
			typedef Status ThreadProcArg;
			//! @copydoc CommonUtil::Traits::ThreadProcSendable::SignalType
			typedef int SignalType;
			//! @copydoc CommonUtil::Traits::ThreadProcSendable::QueueType
			typedef std::deque<Status> QueueType;
		};
		//! Trejt dla wszystkich pośredników, połączenie dwóch powyższych opcji.
		struct InputOutputWorker : public InputWorker, public ThreadProcSendable
		{
			//! @copydoc CommonUtil::Traits::ThreadProcSendable::ThreadProcArg
			typedef Status ThreadProcArg;
			//! @copydoc CommonUtil::Traits::ThreadProcSendable::ThreadProcType
			typedef Status ThreadProcType;
			//! @copydoc CommonUtil::Traits::ThreadProcSendable::SignalType
			typedef boost::signals2::signal<void(Status)> SignalType;
			//! @copydoc CommonUtil::Traits::ThreadProcSendable::QueueType
			typedef std::deque<Status> QueueType;
		};

	};

	using namespace Traits;

	/** Ogólny szablon modułu aplikacji.

		Domyślny przypadek użycia to wywołanie klasy dziedziczącej po tej klasie,
		konkretnie Worker::operator()() - ta metoda obsługuje całą magię
		związaną z synchronizacją, implementuje również wzorzec obserwator.
	*/
	template <typename T>
	class Worker : public Workable
	{
		/** @brief Mutex zabezpieczający kolejkę.
		*/
		std::mutex mtx_;

		/** @brief Zmienna warunkowa, gwarantująca synchronizację.

			Blokuje wykonanie obiektów opartych o trejty dziedziczących po
			CommonUtil::Traits::InputWorker.
		*/
		std::condition_variable cv_;

		/** @brief Zmienna umożliwiająca łagodne zakończenie eksperymentu.
			\sa KillAll
			\todo Może przenieść to do CommonUtil::Workable?
		*/
		static bool good_;

		/** @brief Zmienna obsługująca ewentualne wysyłanie danych w obiekcie.
		*/
		typename T::SignalType signal_;

		/** @brief Kolejka statusów dla szablonów opartych na CommonUtil::Traits::InputWorker.
		*/
		typename T::QueueType queue_;

		/** Implementacja Worker::Connect dla specjalizacji opartych na CommonUtil::Traits::ThreadProcSendable.
			\param observer obiekt, który dostanie status zwrócony w Worker::ThreadProc.
		*/
		template<class U>
		void _Connect(Worker<U> & observer, std::true_type)
		{
			Currently in("Worker::_Connect(true_type)");
			signal_.connect(std::bind(&Worker<U>::Update, std::ref(observer), std::placeholders::_1));
		}

		/** Zabezpiecznie przed użyciem Connect dla obiektu opartego CommonUtil::Traits::InputWorker, które z definicji nie mają żadnych obserwatorów.

			\throws Próba kompilacji spotka się z statycznym assertem.
		*/
		template<class U>
		void _Connect(Worker<U> & observer, std::false_type)
		{
			static_assert(true, "You can't connect anything to non-ThreadProcSendable worker");
		}

		//! Implementacja Worker::Update dla specjalizacji opartych na CommonUtil::Traits::ThreadProcSendable
		void _Update(Status s, std::true_type)
		{
			Currently in("Worker::_Update(true_type)");
			{
				std::lock_guard<std::mutex> l(mtx_);
				queue_.push_back(s);
			}
			cv_.notify_all();
		}

		//! Zabezpiecznie przed stworzeniem specjalizacji dla CommonUtil::Traits::InputWorker. @copydetails _Connect(Worker<U> & observer, std::false_type)
		void _Update(Status s, std::false_type)
		{
			static_assert(true, "You can't worker which isn't InputWorker-based.");
		}

		//! Główna funkcja uruchomiona w wątku dla specjalizacji opartych o CommonUtil::Traits::OutputWorker.
		void _MessageLoop(std::true_type)
		{
			Currently in("Worker::_MessageLooP(std::true_type)");
			Status ret;

			while (good_)
			{
				ret = ThreadProc(0);
				signal_(ret);
			}
		}

		//!  Główna funkcja uruchumiona w wątku dla specjalizacji opartych o CommonUtil::Traits::InputWorker
		void _MessageLoop(std::false_type)
		{
			Currently in("Worker::_MessageLoop(std::false_type)");

			typename T::ThreadProcType ret;
			typename T::ThreadProcArg value;
			std::unique_lock<std::mutex> lk(mtx_);

			while (good_)
			{
				cv_.wait(lk, [&] { return !queue_.empty(); });

				value = queue_.front();
				queue_.pop_front();
				ret = ThreadProc(value);
				_MessageLoop_InputWorker_Send(ret, std::is_base_of<ThreadProcSendable, T>());

			}
		}

		//! Obsługa wartości zwracanych w specjalizacjach CommonUtil::Traits::ThreadProcSendable
		void _MessageLoop_InputWorker_Send(typename T::ThreadProcType & ret, std::true_type)
		{
			Currently in("Worker::_InputWorker_Send(std::true_type)");
			signal_(ret);
		}

		//! Pozostałe przypadki(czyli Traits::InputOnly - teoretycznie tylko wejście.)
		void _MessageLoop_InputWorker_Send(typename T::ThreadProcType & ret, std::false_type)
		{
			Currently in("Worker::_InputWorker_Send(std::false_type)");

			//! @bug przecież aktualna forma wywali aplikację...
			if (ret > 0)
				Worker::KillAll();
		}
	public:

		Worker()  { };


		/** Łączy obserwatora observer z obiektem na rzecz którego wywoływana jest metoda.

			Implementacja wzorca obserwator w oparciu o boost::signals.

		*/
		template <typename U>
		void Connect(Worker<U> & observer)
		{
			Currently in("Worker::Connect()");
			_Connect(observer, std::is_base_of<ThreadProcSendable, T>());
		}

		/** Dodanie statusu do kolejki oczekujących na przetworzenie. */
		void Update(Status s)
		{
			Currently in("Worker::Update()");
			_Update(s, std::is_base_of<InputWorker, T>());
		}

		/** Wywołanie pętli komunikatów */
		void operator()() override
		{
			BOOST_LOG_TRIVIAL(trace) << "Entering Worker::Operator()()";
			_MessageLoop(std::is_base_of<OutputWorker, T>());
		}


		/** Funkcja wywoływana na bieżąco w OutputWorker, w InputWorker tylko w przypadku dorzucenia statusu do kolejki.

		*/
		virtual typename T::ThreadProcType ThreadProc(typename T::ThreadProcArg) = 0;

		/** @brief Zakończenie pracy wszystkich aktywnych obiektów
		 	poprzez przestawienie good_ na false.

		*/
		static void KillAll()
		{
			Currently in("Worker::KillAll()");
			good_ = false;
		}
	};


	template <typename T>
	bool Worker<T>::good_ = true;
};
