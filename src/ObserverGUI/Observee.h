#pragma once
#include<functional>
#include <boost\signals2.hpp>
#include "Status.h"
/*
  abstrakcyjna klasa
  interfejs dla obiektow obserwowanych
  w momencie, gdy zmieniamy wartosc status_ metoda setPossition
  wszystkie funkcje podlaczone metoda connect zostaja wywolane z argumentem status
*/
class Observee
{
public:
	void connect(std::function<void(Status)> slot);
	virtual void setPosition(Status status) = 0;
		
protected:
	Status status_;
	boost::signals2::signal<void(Status)> signal_;
};

