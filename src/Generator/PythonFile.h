#pragma once
#include <string>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <fstream>
#include <regex>

class PythonFile
{
	std::string pFilename_;
	std::string pSource_;
	
	void GetFileContent();
	void CheckFile() const;
public:
	explicit PythonFile(std::string pF);
	std::string ToString() const;

	~PythonFile();
};

