#pragma once
#include "Common.h"
using namespace CommonUtil;

class Kalman : public Worker<Traits::InputOutputWorker>
{

    public:
        Kalman();
        ~Kalman();

	    Status ThreadProc(Status s) override;
};
