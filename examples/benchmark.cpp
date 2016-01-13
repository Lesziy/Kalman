
#include <boost/program_options.hpp>
#include <iostream>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include "Generator.h"
#include <boost/log/expressions.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <string>
#include <thread>

namespace logging = boost::log;
namespace options = boost::program_options;

#ifdef _WIN32
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
	return _iob;
}
#endif


void InitBoostLog(int which)
{
	if (which < 0) which = 0;
	if (which > 5) which = 5;
	using namespace logging::trivial;
	std::array<severity_level, 6> levels = { trace, debug, info, warning, error, fatal };

	logging::core::get()->set_filter
		(
			logging::trivial::severity >= levels[which]
			);
}

static int Counter = 0;

void Foo(Status s)
{
	Counter++;
}

typedef std::chrono::time_point< std::chrono::high_resolution_clock > timepoint_t;

int main(int argc, char* argv[])
{
	options::variables_map vm;
	std::cout << "Script benchmark" << std::endl;
	try
	{
		options::options_description desc("Options");

		desc.add_options()
			("help", "Produce help message")
			("script,s", options::value<std::string>()->default_value("../../maps/standard.py"), "set script path")
			("verbose,v", options::value<int>()->default_value(2), "set verbose level")
			("time,t", options::value<int>()->default_value(1), "benchmark duration")

			;


		options::store(options::parse_command_line(argc, argv, desc), vm);
		options::notify(vm);

		if (vm.count("help"))
		{
			std::cout << desc << std::endl;
			return 0;
		}

		InitBoostLog(vm["verbose"].as<int>());

	}
	catch (std::exception e)
	{
		std::cout << e.what() << std::endl;
		return 1;
	}

	Generator g(vm["script"].as<std::string>());
	g.SetReceiver(Foo);
	g.Start(false);

	timepoint_t endTime = std::chrono::high_resolution_clock::now() + std::chrono::seconds(vm["time"].as<int>());

	BOOST_LOG_TRIVIAL(info) << "Starting...";

	while(std::chrono::high_resolution_clock::now() < endTime)
		g.ExecuteOnce();

	BOOST_LOG_TRIVIAL(info) << "Selected script file: " << vm["script"].as<std::string>();
	BOOST_LOG_TRIVIAL(info) << "Number of received statuses: " << Counter;

}
