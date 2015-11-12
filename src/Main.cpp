#include <iostream>
#include "Generator.h"
//#include "ObserverGUI.h"

std::mutex mtx;

int main(int argc, char **argv)
{
	Generator b("plik.txt");
	//ObserverGUI bb;

	std::cout << "It works!" << std::endl;

	b.Start();
	
    return 0;
}
