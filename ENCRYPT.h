#pragma once
#ifndef CLASSIFICATIONS_H
#define CLASSIFICATIONS_H
#endif 
#ifndef Client_H
#define Client_H
#endif 
#ifndef ExternalVariables_H
#define ExternalVariables_H
#endif
#ifndef MainSystemOperations_H
#define MainSystemOperations_H
#endif
#ifndef stringOperations_H
#define stringOperations_H
#endif
#ifndef Transactions_H
#define Transactions_H
#endif
#ifndef User_H
#define User_H
#endif
#ifndef UserInput_H
#define UserInput_H
#endif
#ifndef Validations_H
#define Validations_H
#endif
#include "Validations.h"
enum enCharType
{
    smallLetter = 1, capitalLetter = 2, specialCharacter = 3, digit = 4
};
namespace enc {
    int generateRandomNumberInRange(int from, int to);
    char generateRandomCharacterBasedOnChoice(enCharType choice);
}