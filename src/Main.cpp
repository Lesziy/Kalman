#include <iostream>
#include "Generator.h"
#include "SimpleSDL.h"
//#include "ObserverGUI.h"


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
