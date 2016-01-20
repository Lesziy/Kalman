#include "Worker.h"
#include "Windows.h"
using namespace CommonUtil;




template<>
void Worker<OutputWorker>::operator()() {
	BOOST_LOG_TRIVIAL(trace) << "Entering OutputWorker operator()";
	Status ret;

	while (good_)
	{
		ret = ThreadProc();
		signal_(ret);
	}


	BOOST_LOG_TRIVIAL(trace) << "Exiting OutputWorker operator()";
}

template<>
void Worker<InputWorker>::operator()() {
	BOOST_LOG_TRIVIAL(trace) << "Entering InputWorker operator()";
	Status s;
	while (good_)
	{
		Sleep(400);
		s = queue_.front();
		queue_.pop_front();
		ThreadProc(s);
	}


	BOOST_LOG_TRIVIAL(trace) << "Exiting OutputWorker operator()";
}



template<>
void Worker<OutputWorker>::Update(Status s)
{

}

template<>
void Worker<InputWorker>::Update(Status s)
{
	queue_.push_back(s);
}
