#include <boost/program_options.hpp>
#include "Common.h"
#include "KalmanFilter.h"
#include "Writer.h"
#include "Generator.h"
#include "SensorWorker.h"

namespace logging = boost::log;
namespace options = boost::program_options;

void Foo(Status s)
      {
		  std::cout << "Got " << s.x << " " << s.y << "at time " << s.time << std::endl;
      }

int main(int argc, char* argv[])
{
	SimpleWorkerPool pool;
	options::variables_map vm;
	std::cout << "Kalman" << std::endl;
    std::chrono::seconds sleepTime;
	try
	{
		options::options_description desc("Options");

		desc.add_options()
			("help,h", "Produce help message")
			("script,s", options::value<std::string>()->default_value("../maps/standard.py"), "set script path")
			("verbose,v", options::value<int>()->default_value(3), "set verbose level")
            ("time,t", options::value<int>()->default_value(1), "set duration of experiment in seconds")
            ;


		options::store(options::parse_command_line(argc, argv, desc), vm);
		options::notify(vm);

		if (vm.count("help"))
		{
			std::cout << desc << std::endl;
			return 0;
		}

		Common::InitBoostLog(vm["verbose"].as<int>());
        sleepTime = std::chrono::seconds(vm["verbose"].as<int>());

	}
	catch (std::exception e)
	{
			std::cout << e.what() << std::endl;
			return 1;
	}

	BOOST_LOG_TRIVIAL(trace) << "entering main()";
	BOOST_LOG_TRIVIAL(info) << "Selected script file: " << vm["script"].as<std::string>();

	KalmanFilter_1D::Vector init_x(2);
	KalmanFilter_1D::Vector init_y(2);

	init_x(1) = 10.0;
	init_y(1) = 0.0;
	init_x(2) = 0.0;
	init_y(2) = 0.0;
	const double time_step = 0.1;
	const double pos_noise = 5.0;
	const double acc_noise = 10;
 
	auto generator = std::make_shared<Generator>(vm["script"].as<std::string>());
	auto writer = std::make_shared<Writer>("output.csv", ';');
	auto sensor = std::make_shared<SensorWorker>(std::pair<double, double>(pos_noise, pos_noise));
	auto kalman = std::make_shared<KalmanFilter>(time_step, pos_noise, acc_noise, init_x, init_y);

	generator->Connect(*sensor);
	sensor->Connect(*kalman);
	sensor->Connect(*writer);
	generator->Connect(*writer);
	kalman->Connect(*writer);

	pool.Register({ generator, kalman, sensor, writer });

	std::thread t(std::ref(pool));

    std::this_thread::sleep_for(sleepTime);

    Worker<CommonUtil::InputWorker>::KillAll();
    Worker<CommonUtil::OutputWorker>::KillAll();
    Worker<CommonUtil::InputOutputWorker>::KillAll();


    t.join();

	BOOST_LOG_TRIVIAL(trace) << "exiting main() gracefully";
    return 0;
}
