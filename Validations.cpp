#pragma once
#include "Validations.h"
using namespace std;
namespace validations
{
	bool checkIfOdd(int c)
	{
		return !(c % 2 == 0);
	}
	bool checkIfEven(int c)
	{
		return !(checkIfOdd(c));
	}
	bool validateIntegerNumberInRange(int num, int from, int to)
	{
		return (num >= from && num <= to);
	}
	bool isPositive(double num)
	{
		return (num > 0);
	}
	bool isNonNegative(double n)
	{
		return (n >= 0);
	}
	bool isNegative(double n)
	{
		return (n < 0);
	}
	bool isUpperAlphabetical(char x)
	{
		return validateIntegerNumberInRange((int)x, 65, 90);
	}
	bool isLowerAlphabetical(char x)
	{
		return validateIntegerNumberInRange((int)x, 97, 122);
	}
	bool isAlphabetical(char x)
	{
		return (isLowerAlphabetical(x) || isUpperAlphabetical(x));
	}
}
