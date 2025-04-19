#pragma once
#include "UserInput.h"
using namespace std;
namespace UserInput {
	bool readBooleanValue(string message)
	{
		int choice;
		cout << message << endl;
		cin >> choice;
		if (choice == 1)
			return true;
		else return false;
	}
	int readNonNegativeInteger(string message)
	{
		int n;
		do
		{
			cout << message << endl;
			cin >> n;
		} while (n < 0);
		return n;
	}
	double readPositivedouble(string message)
	{
		double x;
		do
		{
			cout << message << '\a' << endl;
			cin >> x;
		} while (x <= 0.00000);
		return x;
	}
	string readString(string message)
	{
		string str;
		do
		{
			cout << message << endl;
			getline(cin>>ws, str);
		} while (str.empty());
		return str;
	}
	float readDoubleNumberInRange(string message, double from, double to)
	{
		double num;
		do
		{
			cout << message << '\a' << endl;
			cin >> num;
		} while (num<from || num>to);
		return num;
	}
	int readIntegerNumberInRange(int from, int to, string message) //With input validation provided
	{
		int x;
		do
		{
			cout << message << '\a' << endl;
			while (std::cin.fail() || !(std::cin >> x))
			{
				cout << "Invalid! Please re-enter\n";
				cin.clear();
				cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			}
		} while (x < from || x>to);
		return x;
	}
	int readIntegerNumber(string message)
	{
		int x;
		cout << message << '\a';
		cin >> x;
		return x;
	}
	string readText(string message)
	{
		string text;
		do {
			std::cout << message << std::endl;
			getline(cin, text);
		} while (text.empty());
		return text;
	}
	char readOneCharacter(string message)
	{
		char x;
		cout << message << '\a' << endl;
		cin >> x;
		return x;
	}
	int readPositiveInteger(string message)
	{
		int x;
		do
		{
			cout << message << '\a';
			cin >> x;
		} while (x <= 0);
		return x;
	}
	char readY_or_N_only()
	{
		char x;
		do
		{
			cin >> x;
		} while (tolower(x) != 'y' && tolower(x) != 'n');
		cin.ignore(1, '\n');
		return x;
	}
	double readDoubleValue(string message)
	{
		double n;
		cout << message << endl << '\a';
		cin >> n;
		return n;
	}

}