#include <locale>
#include "Writer.h"
using namespace std;




Writer::Writer(std::string output_file, char separator) : actualTime_(0), separator_(separator)
{
	file_.imbue(std::locale(file_.getloc(), new WriterUtil::punct_facet));
	file_.open(output_file, ios::out | ios::trunc );
	
	if (!file_.is_open())
		throw std::runtime_error("Writer can't open file for writing");

	file_ << "Generator x" << separator_ << "Generator y" << separator_ << "Kalman x" << separator_ << "Kalman y" << endl;
}

Writer::~Writer()
{

}


int Writer::ThreadProc(CommonUtil::Status s)
{
	if (s.type == GENERATOR)
		data_[s.time].first = s;
	else if (s.type == KALMAN)
	{
		BOOST_LOG_TRIVIAL(trace) << "f" << s.x;
		data_[s.time].second = s;
	}

	while((data_[actualTime_].first.type == GENERATOR) && (data_[actualTime_].second.type == KALMAN))
		CommitData(actualTime_++);
	
	return 0;
}

inline void Writer::CommitData(long long number)
{
	BOOST_LOG_TRIVIAL(trace) << "s" << data_[number].second.x;
	file_	<< data_[number].first.x << separator_ << data_[number].first.y << separator_ 
			<< data_[number].second.x << separator_ << data_[number].second.y << endl << flush;
}