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
#include "Classifications.h" 
#include <vector>
#include <fstream>
#include <iomanip>
#include <Windows.h>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <limits>
namespace clients_Operations {
    clientRecord readClientRecord();
    std::string generateClientRecordString(const clientRecord client, std::string delimeter = "#//#");
    clientRecord convertLineDataToRecord(std::string lineData, std::string delimeter = "#//#");
    void printClientRecord(const clientRecord client);
    void addClientStringInfoToFile(std::string fileName, std::string LineRecord);
    void addOneClient(User*& currUsr);
    void addClients(User*& currUsr);
    void printClientDatabaseHeader();
    std::vector<clientRecord> gatherRecordsFromFormattedClientRecordsFile(std::string filename);
    void printTableFormattedOneClientRecord(clientRecord client);
    void printAllClientData(User*& currUsr);
    bool doesClientExistsByAccountNumber(std::string accountNumber, std::vector<clientRecord>& v, clientRecord& cl);
    std::string readAccountNumber();
    bool markAccountForDeletionBasedOnAccountNumber(std::vector<clientRecord>& s, std::string accountNum, User*& currUsr);
    clientRecord generateNewUpdatedClient(const std::string accountNum);
    void saveNonMarkedClientsForDeletionDataToFile(std::string fileName, const std::vector<clientRecord>& s);
    bool deleteClientByAccountNumber(std::vector<clientRecord>& v, std::string accountNum, User*& currUsr);
    bool updateAccountInformationByAccountNumber(std::vector<clientRecord>& v, std::string accountNum, User*& currUsr);
    void printAddNewClientScreen();
    void printDeleteClientScreen();
    void printUpdateClientScreen();
    void printFindClientScreen();
    void findingClient(User*& currUsr);
    void updatingClient(User*& currUsr);
    void deletingClient(User*& currUsr);
    clientRecord modifyExistingClient(std::string accountNumberProvided);
    void addNewClient(User*& currUsr);
    void addingClients(User*& currUsr);
    void showsClientList(User*& currUsr);
    void printClientsBalancesScreenHeader();
    void printOneClientBalanceInformation(const clientRecord s);
    void printAllClientBalanceInformation(User*& currUsr);
}