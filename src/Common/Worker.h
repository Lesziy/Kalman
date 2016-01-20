#include <mutex>
#include <functional>
#include <deque>
#include <boost/signals2.hpp>
#include "Common.h"
#include "Status.h"
#include "Observator.h"
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
		typedef void ThreadProcType;
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
class Worker
{
	std::mutex mtx_;
	bool good_;
	typename T::SignalType signal_;
	typename T::QueueType queue_;
public:

	Worker() : good_(true) { };
	

	template <typename U>
	void Connect(Worker<U> & observer);

	void Update(Status s);
	
	void operator()();

	/** Funkcja wywoływana na bieżąco w OutputWorker, w InputWorker tylko w przypadku dorzucenia statusu do kolejki.
	
	*/
	virtual typename T::ThreadProcType ThreadProc(typename T::ThreadProcArg) = 0;
};

template<>
template<class T>
void Worker<OutputWorker>::Connect(Worker<T> & observer)
{
	signal_.connect(std::bind(&Worker<T>::Update, std::ref(observer), std::placeholders::_1));
}

template<>
template<class T>
void Worker<InputWorker>::Connect(Worker<T> & observer)
{

}