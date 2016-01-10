#pragma once

namespace CommonUtil {
    //struktura w ktorej moga byc przekazywane dane
    enum Type{KALMAN, BODY};

    //! Pojedyncza lokalizacja obiektu.
    struct Status
    {
    	double x;
    	double y;
    	double othr;// to b�dzie powiedzmy ta dodatkowa dana
    	Type type;

    	Status(double px, double py) : x(px), y(py), othr(0), type(KALMAN) {};
    };

};
