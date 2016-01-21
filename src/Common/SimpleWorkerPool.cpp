#include "SimpleWorkerPool.h"
using namespace std::placeholders;

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
			std::thread t(std::ref((*e)));
			threads.push_back(move(t));


		}
		catch(std::exception e)
		{
			return;
		}
	}

	for (int i = 0; i < threads.size(); ++i) threads.at(i).join();

}
