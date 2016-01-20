#pragma once
#include <vector>
#include <algorithm>
#include <initializer_list>
#include <algorithm>
#include <thread>
#include <functional>
#include <boost/any.hpp>
#include "Workable.h"

class SimpleWorkerPool
{
	std::vector<WorkablePtr> workers;
	std::vector<std::thread> threads;

public:
	void Register(std::initializer_list<WorkablePtr>);

	void operator()();
};


