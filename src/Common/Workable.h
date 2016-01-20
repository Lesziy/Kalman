#pragma once

class Workable
{
public:
	virtual void operator()() {};
};

typedef std::shared_ptr<Workable> WorkablePtr;