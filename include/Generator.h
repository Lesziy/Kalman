#pragma once
#include "Common.h"
#define BOOST_PYTHON_STATIC_LIB

#include <string>
#include <mutex>
#include <queue>
#include <boost/python.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>


#include "PythonFile.h"
#include "Trajectory.h"


namespace logging = boost::log;

class Generator
{
	PythonFile pythonFile;
	std::queue<Status> internalQueue;

	void Init();
	void MessageLoop();

	void AddNewStatus(Status st);

public:
	Generator(std::string pFilename);
	~Generator();

	void Start();
};


