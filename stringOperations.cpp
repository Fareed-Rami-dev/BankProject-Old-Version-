#pragma once
#include "stringOperations.h"
using namespace std;
namespace stringOperations
{
    string GenerateLowerCaseString(string str)
    {
        for (int i = 0; i < str.length(); i++)
        {
            if (validations::isUpperAlphabetical(str[i]))
            {
                str[i] = tolower(str[i]);
            }
        }
        return str;
    }
    std::string upperCaseAllEnglishLettersInAGivenString(std::string& text)
    {
        if (text.empty())
        {
            throw std::invalid_argument("String is empty!\n");
        }
        for (int i = 0; i < text.length(); i++)
        {
            if (validations::isLowerAlphabetical(text.at(i)))
            {
                text.at(i) = toupper(text.at(i));
            }
        }
        return text;
    }
    std::string LowerCaseAllEnglishLettersInAGivenString(std::string text)
    {
        if (text.empty())
        {
            throw std::invalid_argument("String is empty!\n");
        }
        for (int i = 0; i < text.length(); i++)
        {
            if (validations::isUpperAlphabetical(text.at(i)))
            {
                text.at(i) = tolower(text.at(i));
            }
        }
        return text;
    }
    vector<std::string> splitStringIntoWordsAndStoreToVector(string text, string delimeter)
    {
        vector<string> strVector; size_t pos; string sWord;
        while ((pos = text.find(delimeter)) != std::string::npos)
        {
            sWord = text.substr(0, pos);
            if (sWord != "")
            {
                strVector.push_back(sWord);
            }
            text.erase(0, pos + delimeter.length());
        }
        if (text != "")
        {
            strVector.push_back(text);
        }
        return strVector;
    }
    string joinVectorStringElementsIntoString(const vector<string>& vec, const string delimeter)
    {
        string v;
        for (const string& str : vec)
        {
            v.append(str);
            v.append(delimeter);
        }
        return v.substr(0, v.length() - delimeter.length());
    }
    string replaceWordsInAGivenString(std::string text, string replaceFrom, string replaceTo, bool matchCase)
    {
        std::vector<std::string> tempVec = splitStringIntoWordsAndStoreToVector(text, " ");
        for (string& str : tempVec)
        {
            if (matchCase) {
                if (str == replaceFrom)
                    str = replaceTo;
            }
            else
            {
                if (LowerCaseAllEnglishLettersInAGivenString(str) == LowerCaseAllEnglishLettersInAGivenString(replaceFrom))
                    str = replaceTo;
            }
        }
        const string delimeter = " ";
        string newString = joinVectorStringElementsIntoString(tempVec, delimeter);
        return newString;
    }
}