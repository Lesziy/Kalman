#include "Generator.h"
//#include "SimpleSDL.h"
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
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace keywords = boost::log::keywords;

#ifdef _WIN32
      FILE _iob[] = { *stdin, *stdout, *stderr };

      extern "C" FILE * __cdecl __iob_func(void)
      {
         return _iob;
      }
#endif
namespace logging = boost::log;

void InitBoostLog()
{
	namespace attrs = boost::log::attributes;
	
	logging::add_file_log
		(
			keywords::file_name = "logKalman_%N.log",
			keywords::rotation_size = 10 * 1024 * 1024,
			keywords::format = "[%TimeStamp% (%ThreadID%)]: %Message%"
		
	);
	logging::core::get()->set_filter
	(
		logging::trivial::severity >= logging::trivial::trace
	);
	boost::shared_ptr< logging::core > core = logging::core::get();
	core->add_global_attribute("Scope", attrs::named_scope());
}
int main(int argc, char* argv[])
{
	using namespace logging::trivial;

	InitBoostLog();
	logging::add_common_attributes();
	
	BOOST_LOG_TRIVIAL(trace) << "entering main()";

	Generator b("plik.txt");
	//SimpleSDL s;

	std::cout << "It works!" << std::endl;

	b.Start();
	wxGUI wx;
	char c;
	std::cin >> c;
	BOOST_LOG_TRIVIAL(trace) << "exiting main() gracefully";
    return 0;
}
