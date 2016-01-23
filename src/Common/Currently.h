#pragma once
#include <boost/log/trivial.hpp>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <string>

namespace CommonUtil
{
    /** Prosta klasa wykorzystująca zasięgi do implementacji wejść do funkcji.

    */
    class Currently
    {
            std::string what_;
            /** Konstruktor.
                \param what nazwa funkcji wyświetlana w BOOST_LOG_TRIVIAL.
            */
public:
            Currently::Currently(std::string what) : what_(what)
            {
                BOOST_LOG_TRIVIAL(trace) << "Entering " << what_;
            }
/*
            //! Destruktor - również wyświetla komunikat o wyjściu z funkcji.
            ~Currently::Currently()
            {
                BOOST_LOG_TRIVIAL(trace) << "Exiting " << what_;
            }
*/    };
}
