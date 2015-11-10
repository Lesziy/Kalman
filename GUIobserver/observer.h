#pragma once
// interfejs obserwowanego
#include "Status.h"
enum Type { KALMAN, BODY };// nie mogê dwukrotnie dziedziczyc z klasy ktora implementuje observer, musze w jakis sposob dowiadywac sie, ktora informacje dostaje
class observer
{
public:
	virtual void refresh(Type type, Status s) = 0;
};

