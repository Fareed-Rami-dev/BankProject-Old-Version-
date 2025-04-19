#pragma once
#include "Validations.h"
using namespace std;
namespace validations
{
	bool isLeapYear(int year)
	{
		if ((year % 400 == 0) || ((!(year % 100 == 0) && year % 4 == 0)))
			return true;
		else return false;
	}

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
	isPrimeOrNot checkIfPrime(int n)
	{
		int M = round(n / 2);
		if (n < 0 || n == 1 || n == 0) return isPrimeOrNot::notPrime;
		if (n == 2 || n == 3) return isPrimeOrNot::prime;
		for (int counter = 2; counter <= M; counter++)
		{
			if (n % counter == 0)
				return isPrimeOrNot::notPrime;
		}
		return isPrimeOrNot::prime;
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
	bool isVowel(const char s)
	{
		switch (tolower(s))
		{
		case 'a': case 'e': case 'i':
		case 'o': case 'u':
			return true;
			break;
		default:
			return false;
		}
	}
}
