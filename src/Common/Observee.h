#pragma once
#include<functional>
#include <boost/signals2.hpp>
#include "Status.h"


namespace CommonUtil {

    //! Interfejs dla obiektow obserwowanych
    /**
      abstrakcyjna klasa -
      w momencie, gdy zmieniamy wartosc metoda Observee::setPosition
      wszystkie funkcje podlaczone metoda connect zostaja wywolane z argumentem f-cji Observee::setPosition

      Przykłady użycia: https://github.com/jpalczewski/Kalman/tree/8d34fe8850c9c91a3ae2750ec68bff0dd8cdffea/src/ObserverGUI
    */
    class Observee
    {
    public:
        /** \todo GCC wymagało jawnych konstruktorów: czy żadne dodatkowe rzeczy nie będą wymagane pod MSVC? */
        Observee() {};
        ~Observee() {};
        //! Łączy sloty.
    	void connect(std::function<void(Status)> slot);
        //! Ustawia nową wartość CommonUtil::Status dla wszystkich obserwujących.
    	virtual void setPosition(Status status) = 0;

    protected:
    	Status status_;
    	boost::signals2::signal<void(Status)> signal_;
    };
};
