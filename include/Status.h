#pragma once
//struktura w ktorej moga byc przekazywane dane
enum Type{KALMAN, BODY};
struct Status
{
	double x;
	double y;
	double othr;// to bêdzie powiedzmy ta dodatkowa dana
	Type type;

	Status(double px, double py) : x(px), y(py), othr(0), type(KALMAN) {};
};