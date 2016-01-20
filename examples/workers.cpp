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
	std::string name;
	int ThreadProc(Status s) override
	{
		BOOST_LOG_TRIVIAL(info) << name << " client got " << s.x;
		return 0;
	}

public:

	Client(std::string in) : name(in) { };

};

class Seller : public Worker<CommonUtil::InputOutputWorker>
{
	std::string name;
	Status ThreadProc(Status s) override
	{
		BOOST_LOG_TRIVIAL(info) << name << " seller got " << s.time;
		s.x = s.time;
		return s;
	}

public:

	Seller(std::string in) : name(in) { };

};

int main()
{
	Common::InitBoostLog(2);
	BOOST_LOG_TRIVIAL(trace) << '1';
	Producer producer;
	Client cli("One");
	Seller Two("Two");

	BOOST_LOG_TRIVIAL(trace) << '2';
	producer.Connect(Two);
	Two.Connect(cli);
	BOOST_LOG_TRIVIAL(trace) << '3';
	
	try
	{
		std::thread u(std::ref(producer));
		std::thread t(std::ref(cli));
		std::thread k(std::ref(Two));

		t.join();
		u.join();
		k.join();
	}
	catch (std::exception e)
	{
		std::cout << e.what();
	}
};
