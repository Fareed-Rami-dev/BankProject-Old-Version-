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

namespace UserInput {
    bool readBooleanValue(std::string message = "Enter choice 1/0\n");
    int readNonNegativeInteger(std::string message = "Enter non negative integer\n");
    double readPositivedouble(std::string message = "Enter a positive double number");
    std::string readString(std::string message = "Please enter a text");
    float readDoubleNumberInRange(std::string message, double from, double to);
    int readIntegerNumberInRange(int from, int to, std::string message);
    int readIntegerNumber(std::string message = "Please enter an integer number");
    std::string readText(std::string message = "Enter text\n");
    char readOneCharacter(std::string message = "Enter a character\n");
    int readPositiveInteger(std::string message = "Enter a positive integer\n");
    char readY_or_N_only();
    double readDoubleValue(std::string message = "Enter a double number\n");
}