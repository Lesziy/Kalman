#include <iostream>
#include <boost/python.hpp>
#include <boost/log/trivial.hpp>
#include "Generator.h"

using namespace GeneratorUtil;


void Generator::Init()
{
	BOOST_LOG_TRIVIAL(trace) << "entering Generator::Init()";
	using namespace boost::python;
	Py_Initialize();

	try {
		mainModule_ = import("__main__");
		mainNamespace_ = mainModule_.attr("__dict__");

		exec(pythonFile_.ToString().c_str(), mainNamespace_);
	} catch(...)
	{
		BOOST_LOG_TRIVIAL(fatal) << "[!] Generator::Init() failed" <<  std::endl;
		throw;
	}
	BOOST_LOG_TRIVIAL(trace) << "exiting Generator::Init()";
}

Status Generator::ExecuteUpdate()
{
	std::array<double, 2> retValue;

	BOOST_LOG_TRIVIAL(trace) << "Generator::ExecuteUpdate()";
	boost::python::object retObject;
	try {
		retObject = eval(pythonFile_.GetFunctionName().c_str(), mainNamespace_);
		retValue = { boost::python::extract<double>(retObject[0]), boost::python::extract<double>(retObject[1]) };
	}
	catch(const boost::python::error_already_set & eas)
	{
		BOOST_LOG_TRIVIAL(error) << "Generator::ExecuteUpdate() failed";
		PyErr_Print();
		throw;
	}

	Status s(retValue[0], retValue[1], time_++, CommonUtil::GENERATOR);
	return s;
}

Status Generator::ThreadProc(int)
{
	BOOST_LOG_TRIVIAL(trace) << "entering Generator::MessageLoop()";
	using namespace boost::python;

		try {
			return ExecuteUpdate();
		}
		catch(std::exception e)
		{
			BOOST_LOG_TRIVIAL(fatal) << "Generator::ExecuteUpdate() catch block: " << e.what();
			PyErr_Print();
			throw;
		}

}

Generator::Generator(	std::string pFilename)
try : pythonFile_(pFilename), time_(0)
{
	Init();
}
catch (...)
{
	BOOST_LOG_TRIVIAL(fatal) << "Generator ctor failed - first script not found, exiting.";
	throw;
}


Generator::~Generator()
{
}
