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
struct permissions
{
	bool canShowClientList;
	bool canAddNewClient;
	bool canDeleteClient;
	bool canUpdateClient;
	bool canFindClient;
	bool hasAccessToTransactions;
	bool canManageUsers;
};
struct User
{
	std::string username;
	std::string password;
	int32_t permissionKey;
	permissions user_permissions = { false,false,false,false,false,false,false };
	bool markAccountFordeletion;
};
struct clientRecord
{
    std::string accountNumber;
	std::string PIN_CODE;
	std::string FullName;
	std::string phone;
    double accountBalance;
    bool markedForDeletion = false;
};

enum managingUsersCommands
{
	listUsers = 1, addingNewUser = 2, DeleteUser = 3, UpdateAUser = 4, FindUser = 5,
	goBackToMainMenu = 6
};
enum MainsysOperations
{
	showClientList = 1, Add_Client = 2, deleteClient = 3,
	updateClientInfo = 4, findClient = 5, transactions = 6, manageUsers = 7, logout = 8
};
enum Transactional_Operations
{
	deposit = 1, withdraw = 2, totalBalances = 3, mainMenu = 4
};
const uint8_t NumberOfUserFieldsInfos = 4;
const int32_t HasAllPermissonsKeyValue = 127;
const double LowerAmmountByFactor = 10e-6;
const std::string adminUsername = "ADMIN";
const std::string currClientFileName = "clientDataRecords.txt";
const int32_t numberOfClientFieldsInfo = 6;
const std::string usersFileName = "Users.txt";
std::string boolToString(bool value);