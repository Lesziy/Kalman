#include "KalmanOptions.h"

using namespace KalmanUtil;


KalmanOptions::KalmanOptions(std::string name)
{
	Currently in("KalmanOptions::KalmanOptions(name)");

	
	try
	{
		boost::property_tree::ptree pt;
		boost::property_tree::ini_parser::read_ini(name, pt);
		TimeStep = pt.get<double>("Config.TimeStep");
		PosNoise = pt.get<double>("Config.PosNoise");
		AccNoise = pt.get<double>("Config.AccNoise");

		Position.x      = pt.get<double>("InitPosition.x");
		Position.y      = pt.get<double>("InitPosition.y");
		Velocity.first  = pt.get<double>("InitVelocity.x");
		Velocity.second = pt.get<double>("InitVelocity.y");
	}
	catch(std::exception e)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Fatal exception in KalmanOptions: " << e.what();
		return;
	}
}