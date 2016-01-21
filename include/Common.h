#pragma once
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <boost/shared_ptr.hpp>

#include "Status.h"
#include "Workable.h"
#include "Worker.h"
#include "SimpleWorkerPool.h"

namespace logging = boost::log;



//! Klasa pozostawiona dla symetrii względem innych klas.
class Common
{

    public:
        Common();
        ~Common();

        static void InitBoostLog(int which);
};
