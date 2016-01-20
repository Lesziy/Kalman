#include "SimpleWorkerPool.h"
#include "Common.h"
using namespace std::placeholders;

#include <typeinfo>

using boost::any_cast;

void SimpleWorkerPool::Register(std::initializer_list<WorkablePtr> list)
{
	for (auto e : list)
		workers.push_back(e);
}

void SimpleWorkerPool::operator()()
{
	threads.reserve(workers.size());
	for(auto e : workers)
	{
		try
		{
			BOOST_LOG_TRIVIAL(trace) << "e: " << typeid(e).name() << ", *e:" << typeid(*e).name();
			std::thread t(std::ref((*e)));

			BOOST_LOG_TRIVIAL(trace) << "t: " << typeid(t).name();// << ", *e:" << typeid(*e).name();
			threads.push_back(move(t));


		}
		catch(std::exception e)
		{
			BOOST_LOG_TRIVIAL(fatal) << e.what();
			return;
		}
	}

	for (int i = 0; i < threads.size(); ++i) threads.at(i).join();

	BOOST_LOG_TRIVIAL(trace) << "SWP OPERATOR" << workers.size() << " " << threads.size();
}
