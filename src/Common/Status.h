#pragma once

namespace CommonUtil {
    //! Etykiety dla nadawców.
    enum Type { NONE,       //!< Wartość zostawiona dla wychwycenia stworzenia obiektu przez domyślny konstruktora.
                GENERATOR,  //!< Wartość przeznaczona dla obiektu Generator
                SENSORS,    //!< Przeznaczone dla obiektu Sensors
                KALMAN      //!< Przeznaczone dla obiektu Kalman
              };

    //! Pojedyncza lokalizacja obiektu.
    struct Status
    {
    	double x;
    	double y;
      long long time;
    	Type type;

      Status() : x(0), y(0), time(0), type(NONE) {};
    	Status(double px, double py, long long ptime, Type who) : x(px), y(py), time(ptime), type(who) {};
    };

};
