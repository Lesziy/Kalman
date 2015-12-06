#pragma once
#include <string>
#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <fstream>

class PythonFile
{
	std::string pFilename_;
	std::string pSource_;
	
	void GetFileContent();
public:
	explicit PythonFile(std::string pF);
	std::string ToString() const;

	~PythonFile();
};

