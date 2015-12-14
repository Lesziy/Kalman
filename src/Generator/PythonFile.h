#pragma once
#include <string>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/filesystem.hpp>
#include <fstream>
#include <regex>

class PythonFile
{
	std::string pFilename_;
	std::string pSource_;
	std::string pFuncName_;


	void GetFileContent();
	std::string GetFilenameWithoutEx() const;

	void CheckFile();
public:
	explicit PythonFile(std::string pF);
	
	const std::string & ToString() const;
	std::string GetFunctionName() const;
	
	~PythonFile();
};

