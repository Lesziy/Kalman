#include "Observee.h"

void Observee::connect(std::function<void(Status)> slot)
{
	signal_.connect(slot);
}
