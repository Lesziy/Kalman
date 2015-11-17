#pragma once
#include <string>
class PythonFile
{
	std::string pFilename;

public:
	explicit PythonFile(std::string pF);
	~PythonFile();
};

