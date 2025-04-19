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
#include <cstdint>
#include <vector>
#include <fstream>
#include <thread>
#include <chrono>
#include <iomanip>
#include "MainSystemOperations.h"

class LogoutException : public std::runtime_error {
public:
    LogoutException(const std::string& message = "User logged out.")
        : std::runtime_error(message) {}
};



namespace User_Operations {
    void printManageUsersScreenHeader();
    void printLoginScreenHeader();
    void printUserListsTableHeader();
    void printAddNewUserScreenHeader();
    void printDeleteUsersScreenHeader();
    void printUpdateUserScreenHeader();
    void printFindUserScreenHeader();
    void printOneUserInfoTableFormatted(const User&);
    std::vector<User> gatherUserRecordsFromFormattedFile(std::string filename);
    bool findUserByUsername(User*& usr);
    void logoutFromUser(User*& currUsr);
    managingUsersCommands selectManagingUserCommandBasedOnChoiceNumber(short num);
    void performManagingUsersCommandBasedOnOperation(managingUsersCommands choice, User*& usr);
    int32_t calculatePermissionKey(User& u);
    void modifyingAUserPermissions(User& u, bool givingFullAccess);
    bool doesUserExists(std::string usernameToSearch, User& u);
    std::string convertUserRecordToStringInfo(const User& u, std::string delimeter = "#//#");
    void saveUserInfoAsStringToFile(std::string filename, const User& userToAdd, User*& currLoggedInUser);
    User modifyExistingUser(std::string previousUserName);
    void AddOneUser(User*& usr);
    bool HasAllPermissions(const User& u);
    bool markUserForDeletion(std::vector<User>& u, std::string username);
    void saveUnmarkedUsersForDeletionToFile(std::string filename, const std::vector<User>& u, User*& currUsr);
    bool doesUserExists(std::string usernameToSearch);
    void deleteUserByUsername(std::vector<User>& s, std::string username, User*& usr);
    void deleteUser(User*& usr);
    void addingUsers(User*& usr);
    void printSpecificUserInfo(const User& u);
    void updateUser(User*& usr);
    bool stringToBoolean(std::string str);
    User convertUserStringInfoToRecord(std::string userInfoStr, std::string delimeterUsed = "#//#");
    void printUserList(User*& usr);
    bool validateLogin(std::string userName, std::string password, User*& currUser, std::vector<User>& s);
    void printManageUsersMenuScreen(User*& usr);
}