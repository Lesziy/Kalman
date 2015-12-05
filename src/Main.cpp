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
namespace logging = boost::log;

#ifdef _WIN32
      FILE _iob[] = { *stdin, *stdout, *stderr };

      extern "C" FILE * __cdecl __iob_func(void)
      {
         return _iob;
      }
#endif


void InitBoostLog()
{
	logging::core::get()->set_filter
	(
		logging::trivial::severity >= logging::trivial::trace
	);
}

int main(int argc, char* argv[])
{
	using namespace logging::trivial;

	InitBoostLog();

	BOOST_LOG_TRIVIAL(trace) << "entering main()";

	Generator b("plik.txt");
	SimpleSDL s;

	std::cout << "It works!" << std::endl;

	b.Start();
	wxGUI wx(argc, argv);
	BOOST_LOG_TRIVIAL(trace) << "exiting main() gracefully";
    return 0;
}
