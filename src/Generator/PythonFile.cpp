#include "PythonFile.h"


void PythonFile::GetFileContent()
{
	BOOST_LOG_TRIVIAL(trace) << "PythonFile::GetFileContent(" << pFilename_ << ")";

	try
	{
		std::ifstream ifs(pFilename_);
		if (!ifs || ifs.bad())
			throw std::exception();

		pSource_.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
	}
	catch(...)
	{
		BOOST_LOG_TRIVIAL(error) << "PythonFile::GetFileContet() failed - can't load file";
		throw;
	}
}

void PythonFile::CheckFile() const
{
	BOOST_LOG_TRIVIAL(trace) << "PythonFile::CheckFile()";

	std::regex regex("def (\\w+)\\(\\):\n(\\s{4}|\\t)");
	std::smatch stringMatches;
	std::string temp = pSource_;
	while (std::regex_search(temp, stringMatches, regex))
	{
		BOOST_LOG_TRIVIAL(debug) << "PythonFile::CheckFile() - std::regex match something: ";
		for (auto a : stringMatches)
			BOOST_LOG_TRIVIAL(debug) << a.str() << " ";
			temp = stringMatches.suffix().str();
	}
	BOOST_LOG_TRIVIAL(trace) << "PythonFile::CheckFile() - ok";

}


PythonFile::PythonFile(std::string pF): pFilename_(pF)
{
	BOOST_LOG_TRIVIAL(trace) << "PythonFile::PythonFile(string)";

	try
	{
		GetFileContent();
		CheckFile();
	}
	catch(...)
	{
		BOOST_LOG_TRIVIAL(error) << "PythonFile ctor failed";
		throw;
	}
	
	BOOST_LOG_TRIVIAL(trace) << "PythonFile ctor exit gracefully";
}

std::string PythonFile::ToString() const
{
	return pSource_;
}

PythonFile::~PythonFile()
{
}
