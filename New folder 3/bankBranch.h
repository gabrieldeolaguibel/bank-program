/*****************************************************************
NAME: Roger Castañer
ORGN: BCSAI-COMPUTER PROGRAMMING 1 22-23, IE University
FILE: bankBranch.h
V1.0 Nov 19th 2022  Split the whole Original File in .h and .cpp files
V2.0 Nov 19th 2022  Created BankBranch::loadClients()
                    Created BankBranch::saveClients()
*****************************************************************/
// C++ code to implement an ATM and
// its basic functions
#include "prePaidCard.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

using namespace std;

#ifndef Included_BankBranch

#define Included_BankBranch

// Class PrePaidCard to get user and Card details

const int MAX_NUMBER_ACCOUNTS = 11;

class BankBranch {
private:
  PrePaidCard client[MAX_NUMBER_ACCOUNTS];
  string name;
  int number_clients;
  int balance;
  string file; // default name of the file with the PrePaidCards
  string blackList_clientsID[MAX_NUMBER_ACCOUNTS] =
      {}; // list of blacklisted clients
  string
      blackList_cardsID[MAX_NUMBER_ACCOUNTS]; // list of blacklisted card IDs\

public:
  BankBranch();
  BankBranch(string);
  void loadBlackList();
  void storeArrayIntoFile();
  string getName();
  void loadClients();
  void saveClients();
  int addUser();
  int viewallUsers();
  int deleteUser(char *);
  void updateUserBalance(char *, double, char);
  int searchSpecificUser(char *, int);
  int searchSpecificUser(char *);
  void setUserLoginDate(int);
  void displayUser(char *);
  int debug();
  int blacklistUser(char *);
  int searchSpecificUserBL(char *);
  int deleteUserFromBlackList(char *);
  bool isBlackListed(char *);
  int changeUserPass(char *);
  int showblacklistUser();
  void showBankBalance();
};

#endif
