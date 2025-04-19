#pragma once
#include <iostream>
#include "User.h";
#include "Transactions.h"
#include <thread>
#include <chrono>
using namespace std;

namespace mainSystemOperations {

	MainsysOperations ChooseMainSysOperationBasedOnChoiceNumber(short num)
	{
		return static_cast<MainsysOperations>(num);
	}

	void printMainMenuScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Main Menu Screen\n");
		printf_s("============================================================\n");
	}

	void print_N_newLines(int8_t num)
	{
		for (int8_t i = 0; i < num; i++)
		{
			putchar('\n');
		}
	}

	void exitCommand()
	{
		system("cls");
		clog << "Program will be exited\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
		exit(7);
	}
	void perfomChosenSystemOperationsBasedOnChoice(MainsysOperations op, User*& currUsr)
	{
		cin.ignore(1,'\n');
		switch (op)
		{
		case MainsysOperations::showClientList:
			clients_Operations::showsClientList(currUsr);
			mainSystemOperations::printMainMenuScreen(currUsr);
			break;
		case MainsysOperations::Add_Client:
			clients_Operations::addingClients(currUsr);
			mainSystemOperations::printMainMenuScreen(currUsr);
			break;
		case MainsysOperations::deleteClient:
			clients_Operations::deletingClient(currUsr);
			mainSystemOperations::printMainMenuScreen(currUsr);
			break;
		case MainsysOperations::updateClientInfo:
			clients_Operations::updatingClient(currUsr);
			mainSystemOperations::printMainMenuScreen(currUsr);
			break;
		case MainsysOperations::findClient:
			clients_Operations::findingClient(currUsr);
			mainSystemOperations::printMainMenuScreen(currUsr);
			break;
		case MainsysOperations::transactions:
			transactions_Operations::printTransactionsMenuScreen(currUsr);
			mainSystemOperations::printMainMenuScreen(currUsr);
			break;
		case MainsysOperations::manageUsers:
			User_Operations::printManageUsersMenuScreen(currUsr);
			break;
		case MainsysOperations::logout:
			User_Operations::logoutFromUser(currUsr);
		default:
		{
			cerr << "Wrong Choice! Please re-launch the program\n";
			mainSystemOperations::exitCommand();
		}
		}
	}
	void printMainMenuScreen(User*& currLoggedInUser)
	{
		system("cls");
		short int choice;
		printMainMenuScreenHeader();
		cout << "\t\t[1] Show Client List.\n";
		cout << "\t\t[2]Add New Client.\n";
		cout << "\t\t[3] Delete Client.\n";
		cout << "\t\t[4]Update Client Info\n";
		cout << "\t\t[5] Find Client.\n";
		cout << "\t\t[6] Transactions.\n";
		cout << "\t\t[7]Manage Users\n";
		cout << "\t\t[8] Logout.\n";
		choice = UserInput::readIntegerNumberInRange(1, 8, "Choose What you want to do [1 to 8]\n");
		perfomChosenSystemOperationsBasedOnChoice(ChooseMainSysOperationBasedOnChoiceNumber(choice), currLoggedInUser);
	}

	void sys_ShowBalances(User*& currUsr)
	{
		if (!currUsr->user_permissions.hasAccessToTransactions)
		{
			cerr << "You don't access to trasnactions... Operation will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		clients_Operations::printAllClientBalanceInformation(currUsr);
	}
}
