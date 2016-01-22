#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Common.h"



namespace WriterUtil
{
	class punct_facet : public std::numpunct<char> {
	protected:
		char do_decimal_point() const
		{
			BOOST_LOG_TRIVIAL(trace) << "w8 m8";
			return ',';
		}
	};
}

class Writer : public CommonUtil::Worker<CommonUtil::Traits::InputWorker>
{
	std::map<long long, std::pair<CommonUtil::Status, CommonUtil::Status>> data_;
	long long actualTime_;
	std::ofstream file_;
	char separator_;

	void CommitData(long long number);



    public:
        Writer(std::string output_fie, char separator);
        ~Writer();

		int ThreadProc(CommonUtil::Status s) override;

};
