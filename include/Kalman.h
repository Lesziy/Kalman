#pragma once
#include "Common.h"
class Kalman : public Worker<CommonUtil::InputOutputWorker>
{
    
    public:
        Kalman();
        ~Kalman();

		Status ThreadProc(Status s);
};

