#include <thread>
#include <chrono>
#include <iostream>
#include "GUI.h"
#include "Sensor.h"
//#include "Kalman.h"
//#include "Body.h"
#include "Status.h"
/*
  Po wielogodzinnych badaniach dochodze do wniosku, ze tak na prawde to nie jest nam potrzebny interfejs do obserwatora,
  bo do signala podpinamy wybrana przez siebie funkcje przyjmujaca odpowiednie argumenty i zwracajaca odpowiednia wartosc
  dodatkowo moglbym u siebie zrobic updateKalman i updateBody osobno i nie musielibysmy miec tego enuma :)
  >>do rozpatrzenia<<
  najlepiej dodac sobie wszystko z boosta do projektu, wtedy bangla, sprawdzone w VS2015
  #############################################
  #############VS tutorial#####################
  #############################################
  Do projektu dodajemy lokalizacje przez:
  Project > nazwa_projektu Properties > C/C++ > General
  i w polu Additional Include Directories wpisujemy odpowiednia sciezke
  lepiej jest przekopiowac potrzebne biblioteki do swojego folderu z projektem,
  sciezka do projektu to $(ProjectDir)
  u mnie na przyklad wyglada to tak: $(ProjectDir)/deps/

  Przemek
*/
GUI* gui = new GUI;
Sensor* sensor = new Sensor;
void kalmanThread()
{
	
}
void bodyThread()
{

}
void guiThread()
{
	while (1)
	{
		gui->printStatus();
		std::this_thread::sleep_for(std::chrono::milliseconds(rand() % 3000));
	}
}
void sensorThread()
{
	Status status;
	double x, y;
	x = y = 0.0;
	status.type = Type::KALMAN;
	while (1)
	{
		status.x = x;
		status.y = y;
		sensor->setPosition(status);
		x+= 0.5; y+= 0.5;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

//Body body;
//Sensor sensor;
//Kalman sensor;
//GUI gui;
int main(int argc, char **argv)
{
	
	sensor->connect(boost::bind(&GUI::update, gui, _1));// to tylko dla pokazowki zrobione
	std::thread t_gui(guiThread); //watek GUI
	std::thread t_sensor(sensorThread); // watek "Sensora"
	std::cout << "GUI" << t_gui.get_id() << "\n"; //do debuggingu :)
	std::cout << "GUI" << t_sensor.get_id() << "\n";
	t_gui.join();
	return 0;
}