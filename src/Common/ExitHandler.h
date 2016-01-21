#pragma once
#include <functional>

#if defined(_WIN64) || defined(_WIN32)

#elif !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))
#include <unistd.h>
#endif


namespace CommonUtil
{
	void SetExitHandler(std::function<void()>)
	{
#if defined(_WIN64) || defined(_WIN32)
		int j;
#elif !defined(_WIN32) && (defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__)))

#endif
	}
};