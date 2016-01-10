#pragma once
#include "Status.h"


namespace CommonUtil {

    /** \brief Interfejs obserwatora do implementowania w klasach projektu

          */
    class Observator
    {
    public:
        //! funkcja czysto wirtualna w klasie pochodnej jest wykozystywana do przesyłania CommonUtil::Status
    	virtual void update(Status status) = 0;
    };

};
