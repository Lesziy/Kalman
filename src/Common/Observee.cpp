#include "Observee.h"

using namespace CommonUtil;

void Observee::connect(std::function<void(Status)> slot)
{
	signal_.connect(slot);
}
