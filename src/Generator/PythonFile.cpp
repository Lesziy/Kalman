#include "PythonFile.h"


void PythonFile::GetFileContent()
{
	BOOST_LOG_TRIVIAL(trace) << "PythonFile::GetFileContent(" << pFilename_ << ")";

	try
	{
		std::ifstream ifs(pFilename_);
		if (!ifs || ifs.bad())
			throw std::runtime_error("File not found or cannot be open.");

		pSource_.assign(std::istreambuf_iterator<char>(ifs), std::istreambuf_iterator<char>());
	}
	catch(...)
	{
		BOOST_LOG_TRIVIAL(error) << "PythonFile::GetFileContet() failed - can't load file";
		throw;
	}
}

std::string PythonFile::GetFilenameWithoutEx() const
{
	boost::filesystem::path p(pFilename_);
	return p.stem().string();
}

void PythonFile::CheckFile()
{
	BOOST_LOG_TRIVIAL(trace) << "PythonFile::CheckFile()";
	
	std::regex regex("def (\\w+)\\(\\):\n(\\s{4}|\\t)");
	std::smatch stringMatches;
	std::string temp = pSource_;
	auto possibleFunc = GetFilenameWithoutEx();
	
	while (std::regex_search(temp, stringMatches, regex))
	{
		for (auto match : stringMatches)
			if(match == possibleFunc)
			{
				BOOST_LOG_TRIVIAL(trace) << "PythonFile::CheckFile() - possibly valid function found.";
				pFuncName_ = match;
				return;
			}
		
		temp = stringMatches.suffix().str();
	}


	BOOST_LOG_TRIVIAL(error) << "PythonFile::CheckFile() failed, regex didn't found any matching functions.";
	throw std::runtime_error("Don't found any matching functions with the filename!");
}


PythonFile::PythonFile(std::string pF): pFilename_(pF), pFuncName_()
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
	
	BOOST_LOG_TRIVIAL(trace) << "PythonFile ctor exitedtes gracefully";
}

std::string PythonFile::ToString() const
{
	return pSource_;
}

std::string PythonFile::GetFunctionName() const
{
	return pFuncName_;
}

PythonFile::~PythonFile()
{
}
