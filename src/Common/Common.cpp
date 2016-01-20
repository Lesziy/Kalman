#include "Common.h"

//! Klasy wspólne dla całego projektu.
namespace CommonUtil
{ };

Common::Common()
{
}

Common::~Common()
{
}


//! Inicjalizacja Boost::log. 
void Common::InitBoostLog(int which)
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
