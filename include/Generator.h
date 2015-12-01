#pragma once
#define BOOST_LOG_DYN_LINK
#include <string>
#include <queue>
#include <Python.h>
#include <boost/python.hpp>
#include "PythonFile.h"
#include "Status.h"


class Generator
{
	PythonFile pythonFile_;

	boost::python::object mainModule_;
	boost::python::object mainNamespace_;

	void Init();
	void MessageLoop();

public:
	Generator(std::string pFilename);
	~Generator();

	void Start();
};
