#include "Common.h"
#include "Worker.h"
#include <thread>
class Producer : public Worker<CommonUtil::OutputWorker>
{
	long long d_;

	Status ThreadProc()
	{
		Status s(0,0, d_++, CommonUtil::NONE);
		return s;
	}

public:
	Producer() : d_(0) { };
	
};

class Client : public Worker<CommonUtil::InputWorker>
{
	void ThreadProc(Status s) override
	{
		BOOST_LOG_TRIVIAL(info) << "client got " << s.time;
	}
};


int main()
{
	BOOST_LOG_TRIVIAL(trace) << '1';
	Producer producer;
	Client cli;

	BOOST_LOG_TRIVIAL(trace) << '2';
	producer.Connect(cli);
	BOOST_LOG_TRIVIAL(trace) << '3';
	try
	{
		std::thread t(std::ref(cli));
		std::thread u(std::ref(producer));

		t.join();
		u.join();
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
};
