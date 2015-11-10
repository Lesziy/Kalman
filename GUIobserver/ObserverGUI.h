#pragma once
#include "observer.h"
#include "Status.h"
#include <vector>
// moj obserwator
class ObserverGUI : public observer
{
public:
	
	void refresh(Type type, Status s);//to bedzie wywolywane w Obserwowanym po zmianie stanu
	~ObserverGUI();
protected:
	Status modifiedKalman;
	Status modifiedBody;
};

