#include "GUI.h"
#include <iostream>
GUI::GUI()
{
	//vectorKalman.lock();//domyœlnie zablokowane
	//vectorBody.lock();
}

GUI::~GUI()
{
}

void GUI::update(Status status)//tutaj bede sobie dopychal te dane po tym
{
	//transmission.lock();
	if (status.type == KALMAN)
	{
		kalmanData.push_back(status);//nalatwiej tak, moze to pozniej zmienie, ale to juz moj problem :)
	}
	if(status.type == BODY)
	{
		bodyData.push_back(status);
	}
	//transmission.unlock();
}
void GUI::printStatus()
{
	if (!kalmanData.empty())
	{
		transmission.lock();
		std::cout << " x= " << kalmanData.begin()->x << " y= " << kalmanData.begin()->y << "\n";
		kalmanData.erase(kalmanData.begin());
		transmission.unlock();
	}
}
/*
void GUI::updateVectorBody()
{
	vectorBody.lock();
	transmission.lock();
	bodyData.push_back(newBody);
	transmission.unlock();//ostrzegam, ¿e jest to bardzo naiwne rozwi¹zanie
}
void GUI::updateVectorKalman()
{
	vectorKalman.lock();
	transmission.lock();
	kalmanData.push_back(newKalman);
	transmission.unlock();//ostrzegam, ¿e jest to bardzo naiwne rozwi¹zanie
}*/