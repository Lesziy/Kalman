#include "Generator.h"
#include "Common.h"
#include <iostream>

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

void Foo(Status s)
      {
		  std::cout << "Got " << s.x << " " << s.y << "at time " << s.time << std::endl;
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
			("script,s", options::value<std::string>()->default_value("../maps/standard.py"), "set script path")
			("verbose,v", options::value<int>()->default_value(3), "set verbose level")
			;


		options::store(options::parse_command_line(argc, argv, desc), vm);
		options::notify(vm);

		if (vm.count("help"))
		{
			std::cout << desc << std::endl;
			return 0;
		}

		Common::InitBoostLog(vm["verbose"].as<int>());

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

	std::cout << "It works!" << std::endl;

	b.Start(false);
	b.ExecuteOnce();
  b.ExecuteOnce();


	BOOST_LOG_TRIVIAL(trace) << "exiting main() gracefully";
    return 0;
}
