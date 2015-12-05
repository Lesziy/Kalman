#include <iostream>
#include <boost/python.hpp>
#include <boost/log/trivial.hpp>
#include "Generator.h"


void Generator::Init()
{
	BOOST_LOG_TRIVIAL(trace) << "entering Generator::Init()";
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
		BOOST_LOG_TRIVIAL(fatal) << "[!] wyjątek w interpreterze!" <<  std::endl;
		throw;
	}
	BOOST_LOG_TRIVIAL(trace) << "exiting Generator::Init()";
}

void Generator::MessageLoop()
{
	BOOST_LOG_TRIVIAL(trace) << "entering Generator::MessageLoop()";
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
			BOOST_LOG_TRIVIAL(fatal) << "error" << std::endl;
			PyErr_Print();
			return;
		}
		std::cout << retValue[0] << " " << retValue[1] << std::endl;
		time_++;

		if (time_ == 2) break;
	}
	BOOST_LOG_TRIVIAL(trace) << "exiting Generator::MessageLoop()";
}

Generator::Generator(std::string pFilename) 
{
	try
	{
		pythonFile_ = PythonFile(pFilename);
	}
	catch(...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "Generator ctor failed - first script not found, exiting.";
		throw;
	}
}

Generator::~Generator()
{
}

void Generator::Start()
{
	Init();
	MessageLoop();
}
