#pragma once
#include "User.h"
#include "Transactions.h"
using namespace std;
void Login()
{
	string userName, password; bool HasAccess;
	User* currUser = nullptr;
	do {
		vector<User> usersSampleInfo = User_Operations::gatherUserRecordsFromFormattedFile(usersFileName);
		system("cls");
		cout << "\t\t\tLogin Screen\n";
		cout << "============================================\n";
		cout << "Enter username\n";
		getline(cin >> ws, userName);
		cout << "Enter password\n";		getline(cin, password);
		HasAccess = User_Operations::validateLogin(userName, password, currUser, usersSampleInfo);
		if (!HasAccess)
		{
			cerr << "Incorrect Username/Password!...Please try again\n";
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		}
		else if (HasAccess)
		{
			mainSystemOperations::printMainMenuScreen(currUser);
		}
	} while (!HasAccess);
}



int main()
{
	while (1)
	{
		try {
			Login();
		}
		catch (const LogoutException& e) {
			std::cout << "Logout successful." << std::endl << std::flush;
			continue;
		}
	}
}

