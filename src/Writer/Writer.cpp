#include <locale>
#include "Writer.h"
using namespace std;




Writer::Writer(std::string output_file, char separator) : actualTime_(0), separator_(separator)
{
	file_.imbue(std::locale(file_.getloc(), new WriterUtil::punct_facet));
	file_.open(output_file, ios::out | ios::trunc );
	
	if (!file_.is_open())
		throw std::runtime_error("Writer can't open file for writing");

	file_ << "Generator x" << separator_ << "Generator y" << separator_ 
		  << "Sensor x" << separator_ << "Sensor y" << separator_
		  << "Kalman x" << separator_ << "Kalman y" << endl;
}

Writer::~Writer()
{

}


int Writer::ThreadProc(CommonUtil::Status s)
{
	if (s.type == GENERATOR) {
		std::get<0>(data_[s.time]) = s;
		//data_[s.time].first = s;
	}
	else if (s.type == SENSORS)
	{
		BOOST_LOG_TRIVIAL(trace) << "f" << s.x;
		std::get<1>(data_[s.time]) = s;
	}
	else if (s.type == KALMAN)
	{
		BOOST_LOG_TRIVIAL(trace) << "f" << s.x;
		std::get<2>(data_[s.time]) = s;
		//data_[s.time].second = s;
	}
	
	while((std::get<0>(data_[actualTime_]).type == GENERATOR) && 
		  (std::get<1>(data_[actualTime_]).type == SENSORS) &&
		  (std::get<2>(data_[actualTime_]).type == KALMAN))
		CommitData(actualTime_++);
	
	return 0;
}

inline void Writer::CommitData(long long number)
{
	CommonUtil::Status* gen_s    = &std::get<0>(data_[number]);
	CommonUtil::Status* sensor_s = &std::get<1>(data_[number]);
	CommonUtil::Status* kalman_s = &std::get<2>(data_[number]);
	
	BOOST_LOG_TRIVIAL(trace) << "s" << kalman_s->x;
	file_	<< gen_s->x << separator_ << gen_s->y << separator_
			<< sensor_s->x << separator_ << sensor_s->y << separator_
		    << kalman_s->x << separator_ << kalman_s->y << separator_ << endl << flush;
}