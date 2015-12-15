#pragma once
//#define BOOST_LOG_DYN_LINK
#include <string>
#include <queue>
#include <Python.h>
#include <boost/python.hpp>
#include <chrono>
#include "PythonFile.h"
#include "Status.h"


class Generator
{
	PythonFile pythonFile_;

	boost::python::object mainModule_;
	boost::python::object mainNamespace_;
	std::chrono::milliseconds waitTime_;

	std::function<void(Status)> receiverFunction_;


	void Init();
	void ExecuteUpdate(std::array<double, 2>& retValue) const;
	void SendUpdate(std::array<double, 2>& retValue);
	void MessageLoop();

public:
	explicit Generator(std::string pFilename, std::chrono::milliseconds waitTime = std::chrono::milliseconds(100));
	~Generator();

	void Start(bool MessageLoop = true);
	void ExecuteOnce();


	void SetReceiver(std::function<void(Status)> what) { receiverFunction_ = what; }
	};


