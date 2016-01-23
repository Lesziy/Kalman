#pragma once
#include <string>
#include <vector>
#include <fstream>
#include "Common.h"


//! Przestrzeń nazw związana z klasą Writer
namespace WriterUtil
{
	//! Klasa używana jako argument do funkcji imbue z biblioteki standardowej.
	class punct_facet : public std::numpunct<char> {
	protected:
		//! Przeciążenie funkcji wirtualnej z biblioteki standardowej, aby wyświetlać przecinek zamiast kropki w csv.
		char do_decimal_point() const
		{
			// \bug Nie działa pod Windowsem.
			return ',';
		}
	};
}

//! Moduł zapisujący pomiary z CommonUtil::GENERATOR i CommonUtil::KALMAN w postaci pliku csv.
class Writer : public CommonUtil::Worker<CommonUtil::Traits::InputWorker>
{
	//! Aktualna kolekcja pomiarów.
	std::map<long long, std::pair<CommonUtil::Status, CommonUtil::Status>> data_;
	//! Liczba ostatniego pomiaru który nie został zapisany do pliku.
	long long actualTime_;
	//! Strumień związany z plikiem.
	std::ofstream file_;
	//! Separator pól w pliku.
	char separator_;

	/** Zapisuje Status z Generator i odpowiadający mu Status z Kalman do pliku.
		\param number pomiary o danej wartości CommonUtil::Status::time zostaną zapisane do pliku. (i usunięte z Writer::data_).
	*/
	void CommitData(long long number);



    public:
		/** Konstruktor.
			\param output_file nazwa pliku wynikowego
			\param separator pól w pliku.
		*/
        Writer(std::string output_file, char separator);
        ~Writer();

		/**	Przeciążanie klasy wykorzystanej w Worker.
		*/
		int ThreadProc(CommonUtil::Status s) override;

};
