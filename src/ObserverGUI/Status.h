#pragma once
//struktura w ktorej moga byc przekazywane dane
enum Type{KALMAN, BODY};
struct Status
{
	double x;
	double y;
	double othr;// to b�dzie powiedzmy ta dodatkowa dana
	Type type;
};