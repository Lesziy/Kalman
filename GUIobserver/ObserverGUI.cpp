#include "ObserverGUI.h"

void ObserverGUI::refresh(Type type, Status data) 
{
	switch (type)
	{
	case KALMAN:
		modifiedKalman = data;
	break;
	case BODY:
		modifiedBody = data;
	break;
	}
}

ObserverGUI::~ObserverGUI()
{
}
