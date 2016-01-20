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

void Generator::ExecuteUpdate(std::array<double, 2>& retValue) const
{
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
}

void Generator::SendUpdate(std::array<double, 2>& retValue)
{
	BOOST_LOG_TRIVIAL(trace) << "Generator::SendUpdate()";
	Status s(retValue[0], retValue[1], time_++, CommonUtil::GENERATOR);
	receiverFunction_(s);

}

Status Generator::ThreadProc()
{
	BOOST_LOG_TRIVIAL(trace) << "entering Generator::MessageLoop()";
	using namespace boost::python;

	while(true)
	{
		try {
			ExecuteOnce();
		}
		catch(std::exception e)
		{
			BOOST_LOG_TRIVIAL(fatal) << "Generator::ExecuteUpdate() catch block: " << e.what();
			PyErr_Print();
			throw;
		}

	}

	BOOST_LOG_TRIVIAL(trace) << "exiting Generator::MessageLoop()";
}

Generator::Generator(	std::string pFilename,
						std::chrono::milliseconds waitTime)
try : pythonFile_(pFilename), waitTime_(waitTime), time_(0)
{ /*function body*/ }
catch (...)
{
	BOOST_LOG_TRIVIAL(fatal) << "Generator ctor failed - first script not found, exiting.";
	throw;
}


Generator::~Generator()
{
}

void Generator::Start(bool MessageLoopEnabled)
{
	Init();

}

void Generator::ExecuteOnce()
{
	std::array<double, 2> retValue;
	ExecuteUpdate(retValue);
	SendUpdate(retValue);
}
