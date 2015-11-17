#include "Generator.h"


extern std::mutex mtx;

void Generator::Init()
{
}

void Generator::MessageLoop()
{
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
