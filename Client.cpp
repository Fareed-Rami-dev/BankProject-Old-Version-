#pragma once
#include "Client.h"
#include "stringOperations.h";
#include "UserInput.h";
#include "User.h";
using namespace std;
namespace clients_Operations {

    clientRecord readClientRecord()
    {
        clientRecord client;
        cout << "Please enter account number\n";
        getline(cin, client.accountNumber);
        cout << "Please enter PIN Code\n";
        getline(cin, client.PIN_CODE);
        cout << "Please enter name\n";
        getline(cin, client.FullName);
        cout << "Enter phone number\n";
        getline(cin, client.phone);
        cout << "Please enter account balance\n";
        cin >> client.accountBalance;
        cin.ignore(1,'\n');
        return client;
    }

    string generateClientRecordString(const clientRecord client, string delimeter)
    {
        string str;
        str.append(client.accountNumber);
        str.append(delimeter);
        str.append(client.PIN_CODE);
        str.append(delimeter);
        str.append(client.FullName);
        str.append(delimeter);
        str.append(client.phone);
        str.append(delimeter);
        str.append(to_string(client.accountBalance));
        str.append(delimeter);
        str.append(boolToString(client.markedForDeletion));
        return str;
    }
    clientRecord convertLineDataToRecord(string lineData, string delimeter)
    {
        vector<string> strVec = stringOperations::splitStringIntoWordsAndStoreToVector(lineData, delimeter);
        if (strVec.size() != numberOfClientFieldsInfo)
        {
            throw std::runtime_error("Can't generate Client Record\n");
        }
        clientRecord client;
        client.accountNumber = strVec[0];
        client.PIN_CODE = strVec[1];
        client.FullName = strVec[2];
        client.phone = strVec[3];
        client.accountBalance = stod(strVec[4]);
        client.markedForDeletion = (strVec[5] == "true" ? true : false);
        return client;
    }
    void printClientRecord(const clientRecord client)
    {
        cout << "Client Info" << endl;
        cout << "Account Number:" << client.accountNumber << endl;
        cout << "PIN CODE: " << client.PIN_CODE << endl;
        cout << "Client Full Name: " << client.FullName << endl;
        cout << "Client Phone Number: " << client.phone << endl;
        cout << "Client Account Balance: " << client.accountBalance << endl;
        cout << "Client To be deleted Status: " << boolToString(client.markedForDeletion)<<endl;
    }
    void addClientStringInfoToFile(string fileName, string LineRecord)
    {
        fstream file;
        file.open(fileName, ios::out | ios::app);
        if (!(file.is_open()))
        {
            throw std::runtime_error("Cannot Open File!\n");
        }
        file << endl << LineRecord << endl;
        file.close();
    }
    void addOneClient(User*& currUsr)
    {
        if (!currUsr->user_permissions.canAddNewClient)
        {
            cerr << "Error: You don't have permission to add new clients.. Operation will be cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return;
        }
        clientRecord client = readClientRecord();
        string str = generateClientRecordString(client);
        addClientStringInfoToFile(currClientFileName, str);
    }

    void addClients(User*& currUsr)
    {
        if (!currUsr->user_permissions.canAddNewClient)
        {
            cerr << "Error: You don't have permission to add new clients.. Operation will be cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return;
        }
        char doYouToAddMoreClients = 'N';
        do
        {
            system("cls");
            cout << "Adding Client..." << endl;
           this_thread::sleep_for(chrono::seconds(3));
            addOneClient(currUsr);
            cout << "If you want to add more clients press Y otherwise press No\n";
            cin >> doYouToAddMoreClients;
        } while (tolower(doYouToAddMoreClients) == 'y');
    }
    void printClientDatabaseHeader()
    {
        cout << "...............................................................................................................\n\n";
        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(10) << "PIN Code";
        cout << "| " << left << setw(40) << "Client Name: ";
        cout << "| " << left << setw(12) << " Phone";
        cout << "| " << left << setw(12) << "Balance:";
        cout << "\n...............................................................................................................\n\n";
    }
    vector<clientRecord> gatherRecordsFromFormattedClientRecordsFile(string filename)
    {
        vector<clientRecord> vecClientsRecord;
        fstream file;
        file.open(filename, ios::in);
        if (!(file.is_open()))
        {
            throw std::runtime_error("Cannot Open File!\n");
        }
        string eachLine;
        while (getline(file, eachLine))
        {
            if (eachLine == "" || eachLine == " ")
                continue;
            clientRecord clientRecord = convertLineDataToRecord(eachLine);
            vecClientsRecord.push_back(clientRecord);
        }
        file.close();
        return vecClientsRecord;
    }
    void printTableFormattedOneClientRecord(clientRecord client)
    {
        cout << "| " << left << setw(15) << client.accountNumber;
        cout << "| " << left << setw(10) << client.PIN_CODE;
        cout << "| " << left << setw(40) << client.FullName;
        cout << "| " << left << setw(12) << client.phone;
        cout << "| " << left << setw(12) << client.accountBalance;
        cout << endl;
    }
    void printAllClientData(User*& currUsr)
    {
        if (!currUsr->user_permissions.canShowClientList)
        {
            cerr << "Error: You don't have permission to list all clients info... Operation is cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return;
        }
        system("cls");
        vector<clientRecord> clients = gatherRecordsFromFormattedClientRecordsFile(currClientFileName);
        cout << "\t\t\t\t\t\tClient List(" << clients.size() << ")" << "Client(s)\n" << endl;
        printClientDatabaseHeader();
        for (clientRecord& C : clients)
        {
            printTableFormattedOneClientRecord(C);
        }
    }
    bool doesClientExistsByAccountNumber(string accountNumber, vector<clientRecord>& v, clientRecord& cl)
    {
        for (clientRecord& r : v)
        {
            if (r.accountNumber == accountNumber) {
                cl = r;
                return true;
            }
        }
        return false;
    }
    string readAccountNumber()
    {
        string accountNo;
        printf_s("Enter the account number\n");
        getline(cin, accountNo);
        return accountNo;
    }
    bool markAccountForDeletionBasedOnAccountNumber(vector<clientRecord>& s, string accountNum, User*& currUsr)
    {
        if (!currUsr->user_permissions.canDeleteClient)
        {
            cerr << "You don't permission to delete user\n";
            this_thread::sleep_for(chrono::seconds(3));
            return false;
        }
        for (clientRecord& cl : s)
        {
            if (cl.accountNumber == accountNum)
            {
                cl.markedForDeletion = true;
                return true;
            }
        }
        return false;
    }
    clientRecord generateNewUpdatedClient(const string accountNum)
    {
        clientRecord client;
        client.accountNumber = accountNum;
        cout << "Enter PIN_CODE\n";
        getline(cin>>ws, client.PIN_CODE);
        cout << "Enter Full Name\n";
        getline(cin, client.FullName);
        cout << "Enter phone\n";
        getline(cin, client.phone);
        cout << "Enter Account Balance\n";
        cin >> client.accountBalance;
       cin.ignore(1,'\n');
        client.markedForDeletion = false;
        return client;
    };
    void saveNonMarkedClientsForDeletionDataToFile(string fileName, const vector<clientRecord>& s)
    {
        fstream file;
        file.open(fileName, ios::out);
        if (!(file.is_open()))
        {
            throw std::runtime_error("File does not exist!\n");
        }
        string clientInfo;
        for (const clientRecord& client : s)
        {
            if (!(client.markedForDeletion))
            {
                clientInfo = generateClientRecordString(client);
                if (clientInfo == " " || clientInfo == "")
                continue;
                file << clientInfo << endl;
            }
        }
        file.close();
    }
    bool deleteClientByAccountNumber(vector<clientRecord>& v, string accountNum, User*& currUsr)
    {
        if (!currUsr->user_permissions.canDeleteClient)
        {
            cerr << "Error: You do not have permission to delete Clients... Operation is cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return false;
        }
        system("cls");
        clientRecord client; char choice = 'n';
        if (doesClientExistsByAccountNumber(accountNum, v, client) == true)
        {
            cout << "Printing Client Info...\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            clients_Operations::printClientRecord(client);
            cout << "---------------------------------------------------------------------------------------------------------------\n";
            cout << "If you want to delete the client press Y or N otherwise\n";
            cin >> choice;
            if (tolower(choice) == 'y') {
                markAccountForDeletionBasedOnAccountNumber(v, accountNum, currUsr);
                saveNonMarkedClientsForDeletionDataToFile(currClientFileName, v);
                v = gatherRecordsFromFormattedClientRecordsFile(currClientFileName);
                cout << "Client Removed Successfully\n";
                this_thread::sleep_for(chrono::seconds(3));
                return true;
            }
            else
            {
                clog << "Deletion Operation for Client with account number: " << accountNum << " has been cancelled\n";
                this_thread::sleep_for(chrono::seconds(3));
                return false;
            }
        }
        else
        {
            cerr << "No Client Exists for client number: " << accountNum << endl;
            this_thread::sleep_for(chrono::seconds(3));
            return false;
        }
    }
    bool updateAccountInformationByAccountNumber(vector<clientRecord>& v, string accountNum, User*& currUsr)
    {
        if (!currUsr->user_permissions.canUpdateClient)
        {
            cerr << "Error: You do not have permisson to update clients.. Operation is cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return false;
        }
        clientRecord client; char choice = 'n';
        if (doesClientExistsByAccountNumber(accountNum, v, client) == true)
        {
            cout << "Printing Client Info....\n";
            std::this_thread::sleep_for(std::chrono::seconds(3));
            clients_Operations::printClientRecord(client);
            cout << "-------------------------------------------------------\n";
            cout << "If you want to update client info press Y otherwise N\n";
            cin >> choice;
            if (tolower(choice) == 'y') {
                clientRecord updatedClient;
                updatedClient = generateNewUpdatedClient(accountNum);
                for (clientRecord& s : v)
                {
                    if (s.accountNumber == updatedClient.accountNumber)
                    {
                        s = updatedClient;
                    }
                }
                saveNonMarkedClientsForDeletionDataToFile(currClientFileName, v);
                cout << "Client Updated Successfully\n";
                this_thread::sleep_for(chrono::seconds(3));
                return true;
            }
            else
            {
                cout << "Operation Upating User with account number: " << accountNum << " has been cancelled\n";
                this_thread::sleep_for(chrono::seconds(3));
                return false;
            }
        }
        else
        {
            cerr << "No account exists.. the operation will be cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return false;
        }
    }

    void printAddNewClientScreen()
    {
        printf_s("============================================================\n");
        printf_s("\t\t\t Add New Clients Screen\n");
        printf_s("============================================================\n");
    }
    void printDeleteClientScreen()
    {
        printf_s("============================================================\n");
        printf_s("\t\t\t Delete Client Screen\n");
        printf_s("============================================================\n");
    }
    void printUpdateClientScreen()
    {
        printf_s("============================================================\n");
        printf_s("\t\t\t Update Client Info Screen\n");
        printf_s("============================================================\n");
    }
    void printFindClientScreen()
    {
        printf_s("============================================================\n");
        printf_s("\t\t\tFind Client Screen\n");
        printf_s("============================================================\n");
    }
    void findingClient(User*& currUsr)
    {
        if (!currUsr->user_permissions.canFindClient)
        {
            cerr << "Permission Denied for finding users\n";
            this_thread::sleep_for(chrono::seconds(3));
            return;
        }
        system("cls");
        string accountNum;
        vector<clientRecord> sampleInfo = gatherRecordsFromFormattedClientRecordsFile(currClientFileName);
        clientRecord searchIfClientExists;
        accountNum = readAccountNumber();
        if (doesClientExistsByAccountNumber(accountNum, sampleInfo, searchIfClientExists))
        {
            cout << "Client Found...The following are the client details\n";
            printClientRecord(searchIfClientExists);
            putchar('\n');
        }
        else
        {
            cout << "Client With Account Number [" << accountNum << "] is not found!" << endl;
        }
        cout << "Press Any Key to go back to Main Menu\n";
        system("pause>0");
    }
    void updatingClient(User*& currUsr)
    {
        if (!currUsr->user_permissions.canUpdateClient)
        {
            cerr << "Error: You do not have permisson to update clients.. Operation is cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return;
        }
        system("cls");
        printUpdateClientScreen();
        string accountNum;
        vector<clientRecord>sampleInfo = gatherRecordsFromFormattedClientRecordsFile(currClientFileName);
        bool doYouWantToUpdateClient = false;
        accountNum = UserInput::readText("Please enter account number\n");
        updateAccountInformationByAccountNumber(sampleInfo, accountNum, currUsr);
        cout << "Press Any Key to go back to Main Menu\n";
        system("pause>0");
    }
    void deletingClient(User*& currUsr)
    {
        if (!currUsr->user_permissions.canDeleteClient)
        {
            cerr << "You don't have permission to delete Client.. Operation will be cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return;
        }
        system("cls");
        printDeleteClientScreen();
        putchar('\n');
        string accountNum; clientRecord searchIfClientAlreadyExists; bool deleteFlagStatus = false;
        accountNum = UserInput::readText("Enter account number\n");
        vector<clientRecord> sampleInfo = gatherRecordsFromFormattedClientRecordsFile(currClientFileName);
        deleteClientByAccountNumber(sampleInfo, accountNum, currUsr);
        printf_s("Press any key to go back to Main Menu\n");
        system("pause>0");
    } 
    clientRecord modifyExistingClient(string accountNumberProvided)
    {
        clientRecord fillClientInfo;
        fillClientInfo.accountNumber = accountNumberProvided;
        cout << "Enter Pin Code";
        getline(cin >> ws, fillClientInfo.PIN_CODE);
        cout << "Enter Full Name: " << endl;
        getline(cin, fillClientInfo.FullName);
        cout << "Enter phone\n";
        getline(cin, fillClientInfo.phone);
        cout << "Enter account balance\n";
        cin >> (fillClientInfo.accountBalance);
       cin.ignore(1,'\n');
        return fillClientInfo;
    }
    void addNewClient(User*& currUsr)
    {
        if (!currUsr->user_permissions.canAddNewClient)
        {
            cerr << "You don't have permission to add Clients.. Operation will be cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return;
        }
        system("cls");
        printAddNewClientScreen();
        clientRecord searchIfClientAlreadyExists;
        vector<clientRecord> sampleInfo = gatherRecordsFromFormattedClientRecordsFile(currClientFileName);
        string accountNum = UserInput::readText("Enter account number\n");
        while ((doesClientExistsByAccountNumber(accountNum, sampleInfo, searchIfClientAlreadyExists)))
        {
            cout << "Client with [" << accountNum << "]" << "already exists, Enter another account number\n";
            getline(std::cin, accountNum);
        }
        putchar('\n');
        clientRecord newClient;
        newClient = modifyExistingClient(accountNum);
        for (int32_t i = 0; i < sampleInfo.size(); i++)
        {
            if (sampleInfo.at(i).accountNumber == accountNum)
            {
                sampleInfo.at(i) = newClient;
                break;
            }
        }
        addClientStringInfoToFile(currClientFileName, (generateClientRecordString(newClient)));
        putchar('\n');
    }
    void addingClients(User*& currUsr)
    {
        if (!currUsr->user_permissions.canAddNewClient)
        {
            cerr << "You don't have permission to add Clients.. Operation will be cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return;
        }
        bool addMoreClients = false;
        do
        {
            addNewClient(currUsr);
            cout << "Client Added Successfully.. do you want to add more clients? Press 1 for yes or 0 for no\n";
            cin >> addMoreClients;
        } while (addMoreClients == true);
        printf_s("Press any key to go back to Main Menu\n");
        system("pause>0");
    }
    void showsClientList(User*& currUsr)
    {
        if (!currUsr->user_permissions.canShowClientList)
        {
            cerr << "Error: You don't have access to show Client List...Operation Will be cancelled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return;
        }
        system("cls");
        printAllClientData(currUsr);
        puts(""); puts("");
        printf_s("Press any key to go back to Main Menu\n");
        system("pause>0");
    }
    void printClientsBalancesScreenHeader()
    {
        cout << "|" << left << setw(18) << "AccountNumber" <<left<< setw(32) << " Full Name" <<"    " << "|" << left << setw(15) << "Account Balance" << endl;
    }
    void printOneClientBalanceInformation(const clientRecord s)
    {
        cout << "| " << left << setw(18) << s.accountNumber <<"| " << setw(32) << s.FullName << " |" << setw(15) << s.accountBalance << endl;
    }
    void printAllClientBalanceInformation(User*& currUsr)
    {
        if (!currUsr->user_permissions.hasAccessToTransactions)
        {
            cerr << "You don't access to trasnactions... Operation will be caneclled\n";
            this_thread::sleep_for(chrono::seconds(3));
            return;
        }
        long double totalBalances = 0;
        vector<clientRecord> sampleInfo = gatherRecordsFromFormattedClientRecordsFile(currClientFileName);
        cout << "\t\t\t\t\t\tBalances List(" << sampleInfo.size() << ")" << "Client(s)\n" << endl;
        printClientsBalancesScreenHeader();
        for (const clientRecord& s : sampleInfo)
        {
            printOneClientBalanceInformation(s);
            totalBalances += (static_cast<long double>(s.accountBalance));
        }
        cout << "_______________________________________________________________________________________________________________\n";
        cout << "\t\t\t\t\tTotal Balances = " << totalBalances << endl;
        cout << "Press Any Key to return To Transactional Menu Screen";
        system("pause>0");
    }
}