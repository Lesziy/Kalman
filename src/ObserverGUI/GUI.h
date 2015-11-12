#pragma once
#include <mutex>
#include <vector>
#include "Status.h"
#include "Observator.h"
//main GUI class
class GUI: public Observator
{
public:
	GUI();
	~GUI();
	void update(Status status);
	void printStatus();
private:
	//void updateVectorBody();
	//void updateVectorKalman();
	//Status newKalman;
	//Status newBody;
	std::vector<Status> kalmanData;
	std::vector<Status> bodyData;
	std::mutex transmission;
	/*std::mutex vectorAccess;
	std::mutex vectorKalman;
	std::mutex vectorBody;*/
};

