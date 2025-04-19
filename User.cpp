#pragma once
#include "User.h"
#include "stringOperations.h"
using namespace std;
namespace User_Operations {

	void printManageUsersScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Manage Users Menu Screen\n");
		printf_s("============================================================\n");
	}

	void printLoginScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Login Screen\n");
		printf_s("============================================================\n");
	}
	void printUserListsTableHeader()
	{
		std::cout << "|" << setw(12) << "User Name" << "|" << setw(12) << " Password" << "|" << setw(4) << "PermissionKey\n";
		std::cout << "______________________________________________________________________________________\n";
	}
	void printAddNewUserScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Add New User Screen\n");
		printf_s("============================================================\n");
	}
	void printDeleteUsersScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Delete Users Screen\n");
		printf_s("============================================================\n");
	}
	void printUpdateUserScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Update Users Screen\n");
		printf_s("============================================================\n");
	}
	void printFindUserScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Find Users Screen\n");
		printf_s("============================================================\n");
	}
	void printOneUserInfoTableFormatted(const User&); //Prototype
	vector<User> gatherUserRecordsFromFormattedFile(string filename); //Prototype
	bool findUserByUsername(User*& usr)
	{
		if (!usr->user_permissions.canManageUsers)
		{
			cerr << "Error: You don't have permisiion to Find Users.. Operation will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(4));
			return false;
		}
		system("cls");
		printFindUserScreenHeader();
		putchar('\n');
		cin.ignore(1,'\n');
		string username = UserInput::readString("Please enter username\n");
		if (username == adminUsername)
		{
			fprintf(stderr, "Access Attempt to Admin Information Deined. You will return to Manage User Menu Screen Soon\n");
			this_thread::sleep_for(chrono::seconds(4));
			return false;
		}
		vector<User>s = gatherUserRecordsFromFormattedFile(usersFileName); //Prototype
		for (const auto& v : s)
		{
			if (v.username == username)
			{
				printf_s("The following are the User details:\n\n");
				cout << "Username: " << v.username << endl;
				cout << "Password: " << v.password << endl;
				cout << "Permission Key Value: " << v.permissionKey << endl;
				cout << "--------------------------------------------------------------------\n\n";
				cout << "You will be returned to Manage User Screen Menu after 12 seconds\n";
				std::this_thread::sleep_for(std::chrono::seconds(12));
				return true;
			}
		}
		printf_s("User not found... you will be returned back to Manage Users Info Soon\n");
		std::this_thread::sleep_for(std::chrono::seconds(3));
		return false;
	}
	void printOneUserInfoTableFormatted(const User& user)
	{
		cout << "|" << setw(12) << user.username << "|";
		if (!(user.username == adminUsername))
			cout << setw(12) << user.password;
		else
		{
			cout << setw(12) << "********";
		}
			cout<< "|" << setw(4) << user.permissionKey << "\n";
	}

	void logoutFromUser(User*& currUsr)
	{
		currUsr = nullptr;
		throw LogoutException();
	}
	managingUsersCommands selectManagingUserCommandBasedOnChoiceNumber(short num)
	{
		return static_cast<managingUsersCommands>(num);
	}
	void performManagingUsersCommandBasedOnOperation(managingUsersCommands, User*&); //Prototype
	void printManageUsersMenuScreen(User*& usr)
	{
		system("cls");
		printManageUsersScreenHeader();
		cout << "\t\t[1] List Users:\n";
		cout << "\t\t[2] Add New User\n";
		cout << "\t\t[3] Delete User\n";
		cout << "\t\t[4] Update User\n";
		cout << "\t\t[5] Find User\n";
		cout << "\t\t[6] Main Menu\n";
		printf_s("============================================================\n");
		const string ManageUsersChoicePrompt = "Choose what do you want to do? [1 to 6]\n";
		short choice = UserInput::readIntegerNumberInRange(1, 6, ManageUsersChoicePrompt);
		performManagingUsersCommandBasedOnOperation(selectManagingUserCommandBasedOnChoiceNumber(choice), usr);
	}
	int32_t calculatePermissionKey(User&); //Prototype
	void modifyingAUserPermissions(User& u, bool givingFullAccess)
	{
		if (givingFullAccess==true)
		{
			u.user_permissions.canAddNewClient = true;
			u.user_permissions.canDeleteClient = true;
			u.user_permissions.canFindClient = true;
			u.user_permissions.canManageUsers = true;
			u.user_permissions.canShowClientList = true;
			u.user_permissions.canUpdateClient = true;
			u.user_permissions.hasAccessToTransactions = true;
			u.permissionKey = HasAllPermissonsKeyValue;
			return;
		}
		else
		{
			printf_s("Do you want to give access to:\n");
			u.user_permissions.canShowClientList = UserInput::readBooleanValue("Show client list? 1/0\n");
			u.user_permissions.canAddNewClient = UserInput::readBooleanValue("Add New Client? 1/0\n");
			u.user_permissions.canDeleteClient = UserInput::readBooleanValue("Delete Client? 1/0\n");
			u.user_permissions.canUpdateClient = UserInput::readBooleanValue("Update Client? 1/0\n");
			u.user_permissions.canFindClient = UserInput::readBooleanValue("Find Client? 1/0\n");
			u.user_permissions.hasAccessToTransactions = UserInput::readBooleanValue("Transactions? 1/0\n");
			u.user_permissions.canManageUsers = UserInput::readBooleanValue("Manager Users? 1/0\n");
			calculatePermissionKey(u);
			return;
		}
	}
	vector<User> gatherUserRecordsFromFormattedFile(string); //Prototype
	bool doesUserExists(string usernameToSearch, User& u)
	{
		vector<User> usersSampleInfo = gatherUserRecordsFromFormattedFile(usersFileName);
		for (int32_t i = 0; i < usersSampleInfo.size(); i++)
		{
			if (usersSampleInfo.at(i).username == usernameToSearch) {
				u = usersSampleInfo.at(i);
				return true;
			}
		}
		return false;
	}
	string convertUserRecordToStringInfo(const User&, string); //Prototype
	void saveUserInfoAsStringToFile(string filename, const User& userToAdd, User*& currLoggedInUser)
	{
		if (!currLoggedInUser->user_permissions.canManageUsers)
		{
			cerr << "Error: You don't have permission to Add Users.. Operation will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		fstream file;
		file.open(filename, ios::app);
		if (!file.is_open())
		{
			throw std::runtime_error("Cannot Open File\n");
		}
		string userInfo = convertUserRecordToStringInfo(userToAdd);
		if (! (userInfo=="" || userInfo==" ") )
		file<<endl<< userInfo << endl;
		file.close();
	}
	User modifyExistingUser(string previousUserName)
	{
		User replaceUserInfo; char hasFullAccess = 'n';
		replaceUserInfo.username = previousUserName;
		replaceUserInfo.markAccountFordeletion = false;
		replaceUserInfo.password = UserInput::readString("Enter new password\n");
		printf_s("Do you want to give full access Y/N\n");
		cin >> hasFullAccess;
		if (tolower(hasFullAccess) == 'y')
		{
			modifyingAUserPermissions(replaceUserInfo, true);
		}
		else
		{
			modifyingAUserPermissions(replaceUserInfo, false);
		}
		return replaceUserInfo;
	}
	void AddOneUser(User*& usr)
	{
		if (!usr->user_permissions.canManageUsers)
		{
			cerr << "Error: You don't have permission to Add Users.. Operation will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		system("cls");
		User newUser; bool giveFullAccess = false; char HasUserAlreadyBeenRegistered = false;
		printAddNewUserScreenHeader();
		cout << "Adding New User:" << endl;
		cout << "Enter username\n";
		do {
			getline(std::cin>>std::ws, newUser.username);
			HasUserAlreadyBeenRegistered = doesUserExists(newUser.username, newUser);
			if (HasUserAlreadyBeenRegistered == true)
			{
				fprintf(stderr, "User with [%s] already exists, Enter another username\n", newUser.username.c_str());
			}
		} while (HasUserAlreadyBeenRegistered == true);
		User temp = newUser;
		temp= modifyExistingUser(newUser.username);
		saveUserInfoAsStringToFile(usersFileName, temp, usr);
		cout << "Please Wait..\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
		cout << "User Added\n";
	}

	bool HasAllPermissions(const User& u)
	{
		return u.permissionKey == HasAllPermissonsKeyValue;
	}
	bool markUserForDeletion(vector<User>& u, string username)
	{
		for (auto& s : u)
		{
			if (s.username == username) {
				if (username != adminUsername)
				{
					s.markAccountFordeletion = true;
					return true;
				}
				else
				{
					std::cerr << "Warning: Cannot Delete Admin\n";
					this_thread::sleep_for(chrono::seconds(3));
					return false;
				}
			}
		}
		return false;
	}
	void saveUnmarkedUsersForDeletionToFile(string filename, const std::vector<User>& u, User*& currUsr)
	{
		if (!currUsr->user_permissions.canManageUsers)
		{
			
			"Error: Permission to modify user list is denied.. Operation will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		fstream file;
		file.open(filename, ios::out);
		if (!(file.is_open()))
		{
			throw std::runtime_error("Cannot Open File!\n");
		}
		string UserStringInfo;
		for (auto& element : u)
		{
			if (!element.markAccountFordeletion)
			{
				UserStringInfo = convertUserRecordToStringInfo(element);
				if (UserStringInfo == " " || UserStringInfo == "")
					continue;
				file << UserStringInfo << endl;
			}
		}
		file.close();
	}
	vector<User> gatherUserRecordsFromFormattedFile(string); //Prototype
	bool doesUserExists(string usernameToSearch)
	{
		vector<User> usersSampleInfo = gatherUserRecordsFromFormattedFile(usersFileName);
		for (int32_t i = 0; i < usersSampleInfo.size(); i++)
		{
			if (usersSampleInfo.at(i).username == usernameToSearch) {
				return true;
			}
		}
		return false;
	}
	void deleteUserByUsername(vector<User>& s, string username, User*& usr)
	{
		if (!usr->user_permissions.canManageUsers)
		{
			cerr << "Error: You don't have permission to Delete Users.. Operation will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		User getUserInfo;
		if (!doesUserExists(username,getUserInfo))
		{
			fprintf(stderr, "User with username (%s) is not found!\n", username.c_str());
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		if (getUserInfo.username == adminUsername)
		{
			cerr << "Warning: Cannot Delete Admin." << endl;
			this_thread::sleep_for(chrono::seconds(3));
		}
		else
		{
			char confirmDeletion = 'n';
			cout << "Printing User Info: " << endl;
			this_thread::sleep_for(chrono::seconds(2));
			cout << "Username: " << getUserInfo.username << endl;
			cout << "Password: " << getUserInfo.password << endl;
			cout << "Permission Key Value: " << getUserInfo.permissionKey << endl;
			cout << "----------------------------------------------------------------------\n";
			cout << "If you want to delete the User Press Y otherwise N\n";
			cin >> confirmDeletion;
			if (tolower(confirmDeletion) == 'y') {
				if (markUserForDeletion(s, username)) {
					saveUnmarkedUsersForDeletionToFile(usersFileName, s, usr);
					clog << "User [" << username << "]" << " deleted successfully\n";
					s = gatherUserRecordsFromFormattedFile(usersFileName);
				}
			}
			else
			{
				clog << "Attempt to delete user with username: [" << getUserInfo.username << "] " << "has been rejected\n";
				cout << "Please wait\n";
				this_thread::sleep_for(chrono::seconds(5));
				return;
			}
			cout << "Please wait..\n";
			this_thread::sleep_for(chrono::seconds(5));
		}
	}
	vector<User> gatherUserRecordsFromFormattedFile(string); //Prototype
	void deleteUser(User*& usr)
	{
		if (!usr->user_permissions.canManageUsers)
		{
			cerr << "Error: You don't have permission to Delete Users.. Operation will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		system("cls");
		User sample;
		printDeleteUsersScreenHeader();
		string username;
		printf_s("Please enter username?");
		getline(cin >> ws, username);
		vector<User> usersSampleInfo = gatherUserRecordsFromFormattedFile(usersFileName);
		deleteUserByUsername(usersSampleInfo, username, usr);
		printf_s("Press any key to go back to Manage Users menu screen\n");
		system("pause>0");
	}
	string convertUserRecordToStringInfo(const User& u, string delimeter)
	{
		string userStringInfo;
		userStringInfo.append(u.username);
		userStringInfo.append(delimeter);
		userStringInfo.append(u.password);
		userStringInfo.append(delimeter);
		userStringInfo.append(to_string(u.permissionKey));
		userStringInfo.append(delimeter);
		userStringInfo.append(boolToString(u.markAccountFordeletion));
		return userStringInfo;
	}
	void addingUsers(User*& usr)
	{
		if (!usr->user_permissions.canManageUsers)
		{
			cerr << "Error: You don't have permission to Add Users.. Operation will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		User u; char doYouWantToAddMoreUsers = 'n';
		do
		{
			AddOneUser(usr);
			printf_s("User Added Successfully, Do you want to add more Users? Y/N\n");
			cin >> doYouWantToAddMoreUsers;
		} while (tolower(doYouWantToAddMoreUsers) =='y');
		clog << "Please Wait you will be returned to Manage Users Menu Screen Soon\n";
		std::this_thread::sleep_for(std::chrono::seconds(7));
	}
	int32_t calculatePermissionKey(User& u)
	{
		if (u.username == adminUsername)
		{
			u.user_permissions.canAddNewClient = true;
			u.user_permissions.canDeleteClient = true;
			u.user_permissions.canFindClient = true;
			u.user_permissions.canManageUsers = true;
			u.user_permissions.canShowClientList = true;
			u.user_permissions.canUpdateClient = true;
			u.user_permissions.hasAccessToTransactions = true;
			u.permissionKey = HasAllPermissonsKeyValue;
			return HasAllPermissonsKeyValue;
		}
		u.permissionKey = 0;
		 int8_t numberOfEnabledPermissions = 0;
		if (u.user_permissions.canShowClientList) {
			u.permissionKey += 1; ++numberOfEnabledPermissions;
		}
		if (u.user_permissions.canAddNewClient) {
			u.permissionKey += 2; ++numberOfEnabledPermissions;
		}
		if (u.user_permissions.canDeleteClient)
		{
			u.permissionKey += 4; ++numberOfEnabledPermissions;
		}
		if (u.user_permissions.canUpdateClient) {
			u.permissionKey += 8; ++numberOfEnabledPermissions;
		}
		if (u.user_permissions.canFindClient) {
			u.permissionKey += 16; ++numberOfEnabledPermissions;
		}
		if (u.user_permissions.hasAccessToTransactions) {
			u.permissionKey += 32; ++numberOfEnabledPermissions;
		}
		if (u.user_permissions.canManageUsers) {
			u.permissionKey += 64; ++numberOfEnabledPermissions;
		}
		u.permissionKey = numberOfEnabledPermissions > 0 ? u.permissionKey : -1;
		return u.permissionKey;
	}
	void printSpecificUserInfo(const User& u)
	{
		cout << "-----------------------------------------------\n";
		cout << "Username: " << u.username << endl;
		if (!(u.username == adminUsername))
			cout << "Password: " << u.password << endl;
		else cout << "**************" << endl;
		cout << "Permission Key: " << u.permissionKey << endl;
		cout << "Marked Account For Delete Status:" << boolToString(u.markAccountFordeletion) << endl;
		cout << "-----------------------------------------------\n";
	}
	void updateUser(User*& usr)
	{
		if (!usr->user_permissions.canManageUsers)
		{
			cerr << "Error: You don't have permisiion to Updaate Users.. Operation will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		system("cls");
		User existingUser;
		char doYouWantToUpdateUser = 'n';
		printUpdateUserScreenHeader();
		string username;
		cout << "Please enter Username?\n";
		getline(cin >> ws, username);

		if (username == adminUsername)
		{
			fprintf(stderr, "Cannot Update Admin Permissions\n");
			printf_s("You will be redirected to Manage Users Menu Screen Soon\n");
			this_thread::sleep_for(chrono::seconds(5));
			return;
		}

		if (!doesUserExists(username, existingUser))
		{
			fprintf(stderr, "User with [%s] does not exists\n", username.c_str());
			printf_s("You will be redirected to Manage Users Menu Screen Soon\n");
			this_thread::sleep_for(chrono::seconds(5));
			return;
		}
		else
		{
			vector<User> usersSampleInfo = gatherUserRecordsFromFormattedFile(usersFileName);
			printOneUserInfoTableFormatted(existingUser);
			cout << "Do you want to update the User Information? Y/N?\n";
			cin >> doYouWantToUpdateUser;
			if (tolower(doYouWantToUpdateUser) == 'y')
			{
				User updatedUser = existingUser;
				updatedUser = modifyExistingUser(existingUser.username);
				for (User& z : usersSampleInfo)
				{
					if (z.username == updatedUser.username)
					{
						z = updatedUser;
						break;
					}
				}
				cout << "User Updated Successfully\n";
				saveUnmarkedUsersForDeletionToFile(usersFileName, usersSampleInfo, usr);
			}
			else
			{
				clog << "Operation to update User with username: " << existingUser.username << " has been rejected\n";
			}
		}
		printf_s("Press Any key to go back to Transactions Menu\n");
		system("pause>0");
	}
	bool stringToBoolean(string str); //Prototype
	User convertUserStringInfoToRecord(string userInfoStr, string delimeterUsed)
	{
		User u; vector<string> a;
		a = stringOperations::splitStringIntoWordsAndStoreToVector(userInfoStr, delimeterUsed);
		if (a.size() != NumberOfUserFieldsInfos)
		{
			throw std::runtime_error("Wrong Delimeter Used or Other Error occured\n");
		}
		u.username = a[0];
		u.password = a[1];
		u.permissionKey = stoi(a[2]);
		u.markAccountFordeletion = stringToBoolean(a[3]);
		if (u.username == adminUsername) {
			u.user_permissions.canAddNewClient = true;
			u.user_permissions.canDeleteClient = true;
			u.user_permissions.canFindClient = true;
			u.user_permissions.canManageUsers = true;
			u.user_permissions.canShowClientList = true;
			u.user_permissions.canUpdateClient = true;
			u.user_permissions.hasAccessToTransactions = true;
			u.permissionKey = HasAllPermissonsKeyValue;
		}
		else {
			if (u.permissionKey & 1)
			{
				u.user_permissions.canShowClientList = true;
			}
			if (u.permissionKey & 2)
			{
				u.user_permissions.canAddNewClient = true;
			}
			if (u.permissionKey & 4)
			{
				u.user_permissions.canDeleteClient = true;
			}
			if (u.permissionKey & 8)
			{
				u.user_permissions.canUpdateClient = true;
			}
			if (u.permissionKey & 16)
			{
				u.user_permissions.canFindClient = true;
			}
			if (u.permissionKey & 32)
			{
				u.user_permissions.hasAccessToTransactions = true;
			}
			if (u.permissionKey & 64)
			{
				u.user_permissions.canManageUsers = true;
			}
		}
		return u;
	}
	vector<User> gatherUserRecordsFromFormattedFile(string filename)
	{
		vector<User> sampleInfo;
		fstream f;
		f.open(filename, ios::in);
		if (!f.is_open())
		{
			throw std::runtime_error("Cannot Open File!\n");
		}
		string eachLine; User U;
		while (getline(f, eachLine))
		{
			if (eachLine == "" || eachLine == " ")
				continue;
			U = convertUserStringInfoToRecord(eachLine);
			sampleInfo.push_back(U);
		}
		return sampleInfo;
	}

	void printUserList(User*& usr)
	{
		if (!usr->user_permissions.canManageUsers)
		{
			cerr << "Error: Access to Users List Denied.. Operation Will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		system("cls");
		vector<User> usersSampleInfo = gatherUserRecordsFromFormattedFile(usersFileName);
		printf_s("\t\t\tUser List(%zu) User%s\n", usersSampleInfo.size(), usersSampleInfo.size() > 1 ? "s" : "");
		cout << "______________________________________________________________________________________\n";
		printUserListsTableHeader();
		putchar('\n'); putchar('\a');
		for (int32_t i = 0; i < usersSampleInfo.size(); i++)
		{
			printOneUserInfoTableFormatted(usersSampleInfo.at(i));
		}
		putchar('\n'); putchar('\n');
		cout << "______________________________________________________________________________________\n";
		cout << "Press any key to go back to Manage Users Menu Screen\n";
		system("pause>0");
	}
	bool validateLogin(string userName, string password, User*& currUser, vector<User>& s)
	{
		for (auto& user : s)
		{
			if (user.username == userName)
			{
				if (user.password == password)
				{
					currUser = &user;
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		return false;
	}

	bool stringToBoolean(string str)
	{
		return stringOperations::LowerCaseAllEnglishLettersInAGivenString(str) == "true";
	}
	void performManagingUsersCommandBasedOnOperation(managingUsersCommands choice, User*& usr)
	{
		switch (choice)
		{
		case managingUsersCommands::listUsers:
			printUserList(usr);
			printManageUsersMenuScreen(usr);
			break;
		case managingUsersCommands::addingNewUser:
			addingUsers(usr);
			printManageUsersMenuScreen(usr);
			break;
		case managingUsersCommands::DeleteUser:
			deleteUser(usr);
			printManageUsersMenuScreen(usr);
			break;
		case managingUsersCommands::UpdateAUser:
			updateUser(usr);
			printManageUsersMenuScreen(usr);
			break;
		case managingUsersCommands::FindUser:
			findUserByUsername(usr);
			printManageUsersMenuScreen(usr);
			break;
		case managingUsersCommands::goBackToMainMenu:
			mainSystemOperations::printMainMenuScreen(usr);
			break;

		}
	}
}

