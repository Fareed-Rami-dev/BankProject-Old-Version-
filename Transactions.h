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

#include <string>
#include <thread>
#include <chrono>
#include "MainSystemOperations.h"
namespace transactions_Operations {

    enum Transactional_Operations {
        deposit = 1,
        withdraw = 2,
        totalBalances = 3,
        mainMenu = 4
    };

    const bool validateAccountBalance(const clientRecord s, const double& withdrawAmount);
    void withDraw(User*& currUsr);
    Transactional_Operations chooseTransactionalOperationBasedOnChoiceNumber(short num);
    void performTransactionalOperationBasedOnChoice(Transactional_Operations op, User*& currUsr);
    void printTransactionsScreenHeader();
    void printTransactionsMenuScreen(User*& currUsr);
    void depositInAccount(User*& currUsr);
    void printDepositScreenHeader();
    void printWithdrawScreenHeader();
}