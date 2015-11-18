#include "Generator.h"


#include <iostream>

void Generator::Init()
{
	std::cout << "hello" << std::flush;
	using namespace boost::python;
	Py_Initialize();
	
	try {
		mainModule_ = import("__main__");
		mainNamespace_ = mainModule_.attr("__dict__");

		exec(
			"i = 0\n"
			"def update():\n"
			"    global i\n"
			"    i = i + 1\n"
			"    return (i,1)\n\n", mainNamespace_);
	} catch(...)
	{
		std::cout << "kurde przypal" <<  std::endl;
	}



	std::cout << "hello2" << std::flush;
}

void Generator::MessageLoop()
{
	using namespace boost::python;
	unsigned int time_ = 0;

	object retObject;
	std::array<double, 2> retValue;

	while(true)
	{
		std::cout << "\n\nNEW\n";
		try {
			retObject = eval("update()", mainNamespace_);
			retValue = { extract<double>(retObject[0]), extract<double>(retObject[1]) };
		}
		catch(...)
		{
			std::cout << "error" << std::endl;
			PyErr_Print();
			return;
		}
		std::cout << retValue[0] << " " << retValue[1] << std::endl;

		time_++;

		if (time_ == 10) break;
	}
}

Generator::Generator(std::string pFilename) : pythonFile_(PythonFile(pFilename))
{
	/*
		Aby nie blokowaæ g³ównego w¹tku ca³¹ inicjalizacjê wyrzucê do osobnego w¹tku
	*/
}

Generator::~Generator()
{
}

void Generator::Start()
{
	Init();
	MessageLoop();
}
