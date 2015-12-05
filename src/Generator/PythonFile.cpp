#include "PythonFile.h"


void PythonFile::GetFileContent()
{
	BOOST_LOG_TRIVIAL(trace) << "PythonFile::GetFileContent(" << pFilename_ << ")";

	try
	{
		std::ifstream ifs(pFilename_);
		if (!ifs || ifs.bad())
			throw std::exception("Can't load file");

		pSource_.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
	}
	catch(...)
	{
		BOOST_LOG_TRIVIAL(error) << "PythonFile::GetFileContet() failed - can't load file";
		throw;
	}
}

PythonFile::PythonFile()
{
	BOOST_LOG_TRIVIAL(trace) << "PythonFile::PythonFile()";
}

PythonFile::PythonFile(std::string pF): pFilename_(pF)
{
	BOOST_LOG_TRIVIAL(trace) << "PythonFile::PythonFile(string)";

	try
	{
		GetFileContent();
	}
	catch(...)
	{
		BOOST_LOG_TRIVIAL(error) << "PythonFile ctor failed";
		throw;
	}
}

std::string PythonFile::ToString() const
{
	return pSource_;
}

PythonFile::~PythonFile()
{
}
