#include "Generator.h"


extern std::mutex mtx;

void Generator::Init()
{
#ifdef KALMAN_DEBUG
	logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::trace);
#elif
	logging::core::get()->set_filter(logging::trivial::severity >= logging::trivial::info);
#endif
	BOOST_LOG_TRIVIAL(trace) << "Generator::Init()";
}

void Generator::MessageLoop()
{
	BOOST_LOG_TRIVIAL(trace) << "Generator::MessageLoop()";
	while(true)
	{
		/*
			je¿eli jest coœ w kolejce => wyœlij to dalej.
		*/
		break;
	}
}

void Generator::AddNewStatus(Status st)
{
	std::lock_guard<std::mutex> lock(mtx);

	internalQueue.push(st);
}

Generator::Generator(std::string pFilename) : pythonFile(PythonFile(pFilename))
{
}

Generator::~Generator()
{
}

void Generator::Start()
{
	Init();
	MessageLoop();
}
