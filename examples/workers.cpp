#include "Common.h"
#include "Worker.h"
#include <thread>
class Producer : public Worker<CommonUtil::OutputWorker>
{
	long long d_;

	Status ThreadProc()
	{
		BOOST_LOG_TRIVIAL(trace) << '5';
		Status s(0,0, d_, CommonUtil::NONE);
		return s;
	}

};

class Client : public Worker<CommonUtil::InputWorker>
{
	void ThreadProc(Status s) override
	{
		BOOST_LOG_TRIVIAL(trace) << '4';
		BOOST_LOG_TRIVIAL(info) << "client got " << s.time;
	}
};


int main()
{
	BOOST_LOG_TRIVIAL(trace) << '1';
	Producer producer;
	Client cli;

	BOOST_LOG_TRIVIAL(trace) << '2';
	//producer.Connect(cli);
	BOOST_LOG_TRIVIAL(trace) << '3';
	try
	{
		std::thread t(std::ref(cli));
		std::thread u(std::ref(producer));
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
};