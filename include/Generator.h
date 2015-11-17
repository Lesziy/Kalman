#pragma once
#define BOOST_ALL_DYN_LINK
#include <string>
#include <mutex>
#include <queue>
#include <boost/python.hpp>

#include "PythonFile.h"
#include "Trajectory.h"
#include "Status.h"


class Generator
{
	PythonFile pythonFile;
	std::queue<Status> internalQueue;

	boost::python::object mainModule;
	boost::python::object mainNamespace;

	void Init();
	void MessageLoop();

	void AddNewStatus(Status st);

public:
	Generator(std::string pFilename);
	~Generator();

	void Start();
};


