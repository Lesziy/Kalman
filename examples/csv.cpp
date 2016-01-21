#include "Writer.h"

int main()
{
	Writer w("plik.csv", ';',',');
	w.ThreadProc(Status(1.1, 2.2, 0, GENERATOR));
	w.ThreadProc(Status(3.3, 4.4, 0, KALMAN));
	w.ThreadProc(Status(1.1, 2.2, 1, GENERATOR));
	w.ThreadProc(Status(3.3, 4.4, 1, KALMAN));
	w.ThreadProc(Status(1.1, 2.2, 2, GENERATOR));
	w.ThreadProc(Status(3.3, 4.4, 2, KALMAN));
	return 0;
}