#include "Generator.h"
#include "SimpleSDL.h"
#include "wxGUI.h"
#include <iostream>

/*Boost.Log related*/
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/program_options.hpp>
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
	std::array<severity_level,6> levels = { trace, debug, info, warning, error, fatal };

	logging::core::get()->set_filter
		(
			logging::trivial::severity >= levels[which]
		);
}

void Foo(Status s)
      {
		  std::cout << "Got " << s.x << " " << s.y << std::endl;
      }

int main(int argc, char* argv[])
{
	options::variables_map vm;
	std::cout << "Kalman" << std::endl;
	try 
	{ 
		options::options_description desc("Options");
		
		desc.add_options()
			("help", "Produce help message")
			("script,s", options::value<std::string>()->default_value("maps/standard.py"), "set script path")
			("verbose,v", options::value<int>()->default_value(3), "set verbose level")
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

	BOOST_LOG_TRIVIAL(trace) << "entering main()";

	BOOST_LOG_TRIVIAL(info) << "Selected script file: " << vm["script"].as<std::string>();
	Generator b(vm["script"].as<std::string>());
	b.SetReceiver(Foo);
	SimpleSDL s;

	std::cout << "It works!" << std::endl;
	
	b.Start();
	wxGUI wx(argc, argv);
	BOOST_LOG_TRIVIAL(trace) << "exiting main() gracefully";
    return 0;
}
