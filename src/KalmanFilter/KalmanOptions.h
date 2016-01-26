#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/ini_parser.hpp>
#include <string>

#include "Common.h"

using namespace CommonUtil;

namespace KalmanUtil {

	class KalmanOptions
	{


	public:
		KalmanOptions(std::string name);


		Status Position;
		std::pair<double, double> Velocity;
		double TimeStep;
		double PosNoise;
		double AccNoise;
	};

}