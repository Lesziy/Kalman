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

		Position.first.x = pt.get<double>("FirstPosition.x");
		Position.first.y = pt.get<double>("FirstPosition.y");
		Position.second.x = pt.get<double>("SecondPosition.x");
		Position.second.y = pt.get<double>("SecondPosition.y");
	}
	catch(std::exception e)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Fatal exception in KalmanOptions: " << e.what();
		return;
	}
}