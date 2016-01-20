#include "Common.h"
#include "Worker.h"
#include <thread>
#include "SimpleWorkerPool.h"

class Producer : public Worker<CommonUtil::OutputWorker>
{
	long long d_;

	Status ThreadProc()
	{
		Status s(-d_,0, d_++, CommonUtil::NONE);
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

#define SWPR(x) 
int main()
{	
	Common::InitBoostLog(2);


	auto producer = std::make_shared<Producer>();
	auto client = std::make_shared<Client>("Last");
	auto better = std::make_shared<Client>("Klient lepszego sortu");
	auto seller = std::make_shared<Seller>("Middle");
	SimpleWorkerPool swp;


	producer->Connect(*better);
	producer->Connect(*seller);
	seller->Connect(*client);
	
	swp.Register({ producer, client, seller, better });
	
	swp();
};
