#pragma once
#include "Common.h"

#include <string>
#include <mutex>
#include <queue>
#include <boost/python.hpp>

#include "PythonFile.h"
#include "Trajectory.h"



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


