#include <mutex>
#include <functional>
#include <deque>
#include <boost/signals2.hpp>
#include <type_traits>
#include <condition_variable>
#include "Common.h"
#include "Status.h"
#include "Workable.h"

namespace CommonUtil {
	//! Trejt który umożliwia Worker wysyłanie danych.
	struct ThreadProcSendable
	{
		typedef Status ThreadProcType;
		typedef void ThreadProcArg;
		typedef boost::signals2::signal<void(Status)> SignalType;
		typedef int QueueType;
	};

	//! Trejt który określa moduły tylko nadające informację(np. Generator )
	struct OutputWorker : public ThreadProcSendable { };
	//! Trejt który określa moduły jedynie przyjmujące dane.(np. Writer )
	struct InputWorker
	{
		typedef int ThreadProcType;
		typedef Status ThreadProcArg;
		typedef int SignalType;
		typedef std::deque<Status> QueueType;
	};
	//! Trejt dla wszystkich pośredników, połączenie dwóch powyższych opcji.
	struct InputOutputWorker : public InputWorker, public ThreadProcSendable
	{
		typedef Status ThreadProcArg;
		typedef Status ThreadProcType;
		typedef boost::signals2::signal<void(Status)> SignalType;
		typedef std::deque<Status> QueueType;
	};
	

};

using namespace CommonUtil;

//! Ogólny szablon modułu aplikacji.
template <typename T>
class Worker : public Workable
{
	std::mutex mtx_;
	std::condition_variable cv_;

	static bool good_;
	typename T::SignalType signal_;
	typename T::QueueType queue_;

	//! Funkcja wywoływana tylko dla pochodnych CommonUtil::ThreadProcSendable, czyli klas które wysyłają dane.
	template<class U>
	void _Connect(Worker<U> & observer, std::true_type)
	{
		BOOST_LOG_TRIVIAL(trace) << "Entering _Connect(true_type)";
		signal_.connect(std::bind(&Worker<U>::Update, std::ref(observer), std::placeholders::_1));
	}

	template<class U>
	void _Connect(Worker<U> & observer, std::false_type)
	{
		static_assert(true, "You can't connect anything to non-ThreadProcSendable worker");
	}

	void _Update(Status s, std::true_type)
	{
		BOOST_LOG_TRIVIAL(trace) << "Entering Worker::_Update(true_type)";
		{
			std::lock_guard<std::mutex> l(mtx_);
			queue_.push_back(s);
		}
		cv_.notify_all();
	}

	void _Update(Status s, std::false_type)
	{
		static_assert(true, "You can't worker which isn't InputWorker-based.");
	}

	//! Pętla dla output-worker
	void _MessageLoop(std::true_type)
	{
		BOOST_LOG_TRIVIAL(trace) << "Entering OutputWorker operator()()";
		Status ret;

		while (good_)
		{
			ret = ThreadProc();
			signal_(ret);
		}


		BOOST_LOG_TRIVIAL(trace) << "Exiting OutputWorker operator()()";
	}

	void _MessageLoop(std::false_type)
	{
		BOOST_LOG_TRIVIAL(trace) << "Entering InputWorker-based operator()()";
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

	void _MessageLoop_InputWorker_Send(typename T::ThreadProcType & ret, std::true_type)
	{
		signal_(ret);
	}

	void _MessageLoop_InputWorker_Send(typename T::ThreadProcType & ret, std::false_type)
	{
		if (ret > 0) 
			Worker::KillAll();
	}
public:

	Worker()  { };
	

	template <typename U>
	void Connect(Worker<U> & observer)
	{
		BOOST_LOG_TRIVIAL(trace) << "Entering Worker::Connect()";
		_Connect(observer, std::is_base_of<ThreadProcSendable, T>());
		BOOST_LOG_TRIVIAL(trace) << "Exiting Worker::Connect()";
	}

	void Update(Status s)
	{
		BOOST_LOG_TRIVIAL(trace) << "Entering Worker::Update()";
		_Update(s, std::is_base_of<InputWorker, T>());
		BOOST_LOG_TRIVIAL(trace) << "Exiting Worker::Update()";
	}
	
	void operator()() override
	{
		BOOST_LOG_TRIVIAL(trace) << "Entering Worker::Operator()()";
		_MessageLoop(std::is_base_of<OutputWorker, T>());
	}


	/** Funkcja wywoływana na bieżąco w OutputWorker, w InputWorker tylko w przypadku dorzucenia statusu do kolejki.
	
	*/
	virtual typename T::ThreadProcType ThreadProc(typename T::ThreadProcArg) = 0;

	static void KillAll()
	{
		good_ = false;
	}
};


template <typename T>
bool Worker<T>::good_ = true;