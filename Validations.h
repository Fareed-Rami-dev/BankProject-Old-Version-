#pragma once
#ifndef CLASSIFICATIONS_H
#define CLASSIFICATIONS_H
#endif 
#ifndef Client_H
#define Client_H
#endif 
#ifndef ENCRYPT_H
#define ENCRYPT_H
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
#include <iostream>
#include <string>
namespace validations {
    bool checkIfOdd(int c);
    bool checkIfEven(int c);
    bool validateIntegerNumberInRange(int num, int from, int to);
    bool isPositive(double num);
    bool isNonNegative(double n);
    bool isNegative(double n);
    bool isUpperAlphabetical(char x);
    bool isLowerAlphabetical(char x);
    bool isAlphabetical(char x);
}