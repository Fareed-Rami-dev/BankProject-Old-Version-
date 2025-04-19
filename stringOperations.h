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
#include "Validations.h"
#include <vector>
enum whatToCount {
    LowerCaseEnglishLetters = 1,
    upperCaseEnglishLetters = 2,
    All = 3
};

namespace stringOperations {
    std::string GenerateLowerCaseString(std::string str);
    std::string upperCaseAllEnglishLettersInAGivenString(std::string& text);
    std::string LowerCaseAllEnglishLettersInAGivenString(std::string text);
    std::vector<std::string> splitStringIntoWordsAndStoreToVector(std::string text, std::string delimeter="#//#");
   std::string joinVectorStringElementsIntoString(const std::vector<std::string>& vec, const std::string delimeter="#//#");
    std::string replaceWordsInAGivenString(std::string text, std::string replaceFrom, std::string replaceTo, bool matchCase = true);
}