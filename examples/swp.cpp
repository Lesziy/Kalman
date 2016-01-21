#include "Common.h"
#include <string>

struct BB : public Workable
{
	std::string D;
	void operator()() override
	{
		BOOST_LOG_TRIVIAL(trace) << "BB: " << D;
	}
};

int main()
{
	BB a, c, d;
	a.D = "Aha";
	c.D = "Lol";
	d.D = "Ok";

	Workable b = d;
	SimpleWorkerPool swp;

	swp.Register({std::make_shared<BB>(a), std::make_shared<BB>(d)});
	swp();

	return 0;
}