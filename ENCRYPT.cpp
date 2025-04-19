#pragma once
#include "ENCRYPT.h"
#include "UserInput.h"
#include <string>
using namespace std;

namespace enc
{
	int generateRandomNumberInRange(int from, int to)
	{
		if (from > to)
		{
			throw std::invalid_argument("Initial Value cannot be larger than the final value\n");
		}
		else
		{
			return (rand() % (to - from + 1) + from);
		}
	}
	char generateRandomCharacterBasedOnChoice(enCharType choice)
	{
		switch (choice)
		{
		case enCharType::capitalLetter:
			return char(generateRandomNumberInRange(65, 90));
		case  enCharType::smallLetter:
			return char(generateRandomNumberInRange(97, 122));
		case enCharType::specialCharacter:
			return char(generateRandomNumberInRange(33, 47));
		case enCharType::digit:
		default: //Default Case is Digit
			return char(generateRandomNumberInRange(48, 57));
		}
	}
}