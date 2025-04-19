#pragma once
#include "Transactions.h"
#include "User.h"
using namespace std;
namespace transactions_Operations
{
	const bool validateAccountBalance(const clientRecord s, const double& withdrawAmount); //Prototype
	void withDraw(User*& currUsr)
	{
		if (!currUsr->user_permissions.hasAccessToTransactions)
		{
			cerr << "You don't access to trasnactions... Operation will be caneclled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		string accountNum; double amountToWithdraw; char confirmWithdraw = 'n';
		clientRecord client;
		vector<clientRecord> sampleInfo = clients_Operations::gatherRecordsFromFormattedClientRecordsFile(currClientFileName);
		accountNum = UserInput::readText("Please enter account number\n");
		while (!(clients_Operations::doesClientExistsByAccountNumber(accountNum, sampleInfo, client)))
		{
			cout << "Account with Number:[" << accountNum << "]" << " does not exist.. Please enter a new account Number\n";
			getline(cin, accountNum);
		}
		putchar('\n');
		cout << "The following are the clients details:\n--------------------------\n" << endl;
		clients_Operations::printClientRecord(client);
		std::cout << std::endl;
		const string withdrawPrompt = "Please enter vaid amount to withdraw\n";
		amountToWithdraw = UserInput::readPositivedouble(withdrawPrompt);
		while (!(validateAccountBalance(client, amountToWithdraw)))
		{
			cout << "Amount Exceeds the balance, you can withdraw up to: " << client.accountBalance-LowerAmmountByFactor << endl;
			amountToWithdraw = UserInput::readPositivedouble(withdrawPrompt);
		}
		cout << "Are you sure you want to perform this transaction? y/n ?";
		cin >> confirmWithdraw;
		cin.ignore(1,'\n');
		if (tolower(confirmWithdraw) == 'y')
		{
			client.accountBalance -= (amountToWithdraw);
			for (clientRecord& s : sampleInfo)
			{
				if (s.accountNumber == accountNum) {
					s.accountBalance = client.accountBalance;
					break;
				}
			}
			clients_Operations::saveNonMarkedClientsForDeletionDataToFile(currClientFileName, sampleInfo);
			cout << "Please wait....\n";
			std::this_thread::sleep_for(std::chrono::seconds(5));
			cout << "Amount of " << amountToWithdraw << " has been withdrawed successfully\n";
		}
		else
		{
			clog << "Withdraw amount of: " << amountToWithdraw << " from account number:" << accountNum << " rejected\n";
		}
		cout << "You will be redirected to Transactional Operations Menu Soon\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	Transactional_Operations chooseTransactionalOperationBasedOnChoiceNumber(short num)
	{
		return static_cast<Transactional_Operations>(num);
	}
	void performTransactionalOperationBasedOnChoice(Transactional_Operations, User*&); //Prototype
	void printTransactionsScreenHeader(); //Prototype
	void printTransactionsMenuScreen(User*& currUsr)
	{
		system("cls");
		if (!currUsr->user_permissions.hasAccessToTransactions)
		{
			cerr << "Error: You don't have access to Trasnactions.. Operation will be cancelled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		system("cls");
		printTransactionsScreenHeader();
		const string TMS_prompt = "Choose what do you want to do ? [1 to 4]\n";
		short choiceNum;
		cout << "\t\t[1] Deposit\n";
		cout << "\t\t[2] Withdraw\n";
		cout << "\t\t[3] Total Balances\n";
		cout << "\t\t[4] Main Menu\n";
		choiceNum = UserInput::readIntegerNumberInRange(1, 4, TMS_prompt);
		performTransactionalOperationBasedOnChoice(chooseTransactionalOperationBasedOnChoiceNumber(choiceNum), currUsr);
	}
	void depositInAccount(User*&); //Prototype

	void depositInAccount(User*& currUsr)
	{
		if (!currUsr->user_permissions.hasAccessToTransactions)
		{
			cerr << "You don't access to trasnactions... Operation will be caneclled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		string accountNum; double amountToDeposit; char confirmDeposit = 'n';
		accountNum = UserInput::readText("Please enter acccout number\n");
		clientRecord client;
		vector<clientRecord> sampleInfo = clients_Operations::gatherRecordsFromFormattedClientRecordsFile(currClientFileName);
		while (!(clients_Operations::doesClientExistsByAccountNumber(accountNum, sampleInfo, client)))
		{
			cout << "Account with Number:[" << accountNum << "]" << " does not exist.. Please enter a new account Number\n";
			getline(cin, accountNum);
		}
		putchar('\n');
		cout << "The following are the clients details:\n--------------------------\n" << endl;
		clients_Operations::printClientRecord(client);
		const string depositPrompt = "Please enter valid amount to deposit\n";
		amountToDeposit = UserInput::readPositivedouble(depositPrompt);
		cout << "Are you sure you want to perform this transaction? y/n";
		cin >> confirmDeposit;
		cin.ignore(1,'\n');
		if (tolower(confirmDeposit) == 'y')
		{
			client.accountBalance += amountToDeposit;
			for (clientRecord& s : sampleInfo)
			{
				if (s.accountNumber == accountNum) {
					s.accountBalance = client.accountBalance;
					break;
				}
			}
			clients_Operations::saveNonMarkedClientsForDeletionDataToFile(currClientFileName, sampleInfo);
			cout << "Please wait....\n";
			std::this_thread::sleep_for(std::chrono::seconds(7));
			cout << "Amount of " << amountToDeposit << " has been deposited successfully\n";
		}
		else
		{
			clog << "Account Deposit For Account Number:[" << accountNum << "]" << " rejected\n";
		}
		cout << "You will be redirected to Transactional Operations Menu Soon\n";
		std::this_thread::sleep_for(std::chrono::seconds(5));
	}
	const bool validateAccountBalance(const clientRecord s, const double& withdrawAmount)
	{
		return (withdrawAmount <= s.accountBalance - (LowerAmmountByFactor));
	}
	void printTransactionsScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Transactions Menu Screen\n");
		printf_s("============================================================\n");
	}
	void printDepositScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Deposit Screen\n");
		printf_s("============================================================\n");
	}
	void printWithdrawScreenHeader()
	{
		printf_s("============================================================\n");
		printf_s("\t\t\t Withdraw Screen\n");
		printf_s("============================================================\n");
	}
	void performTransactionalOperationBasedOnChoice(Transactional_Operations op, User*& currUsr)
	{
		cin.ignore(1, '\n');
		if (!currUsr->user_permissions.hasAccessToTransactions)
		{
			cerr << "You don't access to trasnactions... Operation will be caneclled\n";
			this_thread::sleep_for(chrono::seconds(3));
			return;
		}
		switch (op)
		{
		case Transactional_Operations::deposit:
			depositInAccount(currUsr);
			printTransactionsMenuScreen(currUsr);
			break;
		case Transactional_Operations::withdraw:
			withDraw(currUsr);
			printTransactionsMenuScreen(currUsr);
			break;
		case Transactional_Operations::totalBalances:
			mainSystemOperations::sys_ShowBalances(currUsr);
			printTransactionsMenuScreen(currUsr);
			break;
		case Transactional_Operations::mainMenu:
			mainSystemOperations::printMainMenuScreen(currUsr);
			break;
		default:
		{
			throw std::invalid_argument("Invalid Transactional Operation Choice!\n");
		}
		}
	}
}