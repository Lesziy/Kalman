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
		std::cout << "[!] wyjątek w interpreterze!" <<  std::endl;
		throw;
	}
	std::cout << "Python is working!\n" << std::endl;
}

void Generator::MessageLoop()
{
	std::cout << "MessageLoop();"<< std::endl;
	using namespace boost::python;
	unsigned int time_ = 0;

	object retObject;
	std::array<double, 2> retValue;

	std::cout << "\nCyferki wygenerowane w pythonie: " << std::endl;

	while(true)
	{
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

		if (time_ == 2) break;
	}
}

Generator::Generator(std::string pFilename) : pythonFile_(PythonFile(pFilename))
{
	/*
		Aby nie blokowa� g��wnego w�tku ca�� inicjalizacj� wyrzuc� do osobnego w�tku
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
