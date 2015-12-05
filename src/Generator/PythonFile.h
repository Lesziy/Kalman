#pragma once
#include <string>
#include <boost/log/trivial.hpp>
#include <fstream>

class PythonFile
{
	std::string pFilename_;
	std::string pSource_;
	
	void GetFileContent();
public:
	PythonFile();
	PythonFile(std::string pF);
	std::string ToString() const;

	~PythonFile();
};

