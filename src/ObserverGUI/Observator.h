#pragma once
#include "Status.h"
/* interfejs obserwator
  zaimplementowana funkcja update w klasie pochodnej jest wykozystywana do
  przesylania statusu
*/
class Observator
{
public:
	virtual void update(Status status) = 0;
};

