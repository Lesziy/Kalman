#include "Generator.h"
#include "SimpleSDL.h"
#include <iostream>
//#include "ObserverGUI.h"

/*
	Bez tego nie działa. g8 work, VS.
*/
FILE _iob[] = { *stdin, *stdout, *stderr };

extern "C" FILE * __cdecl __iob_func(void)
{
   return _iob;
}

std::mutex mtx;
	int main(int argc, char* argv[])
{
	Generator b("plik.txt");
	SimpleSDL s;

	//ObserverGUI bb;

	std::cout << "It works!" << std::endl;

	b.Start();

    return 0;
}
