/*****************************************************************
NAME: Roger Castañer 
ORGN: BCSAI-COMPUTER PROGRAMMING 1 22-23, IE University
FILE: prePaidCard.h 
V1.0 Nov 19th 2022  Split the whole Original File in .h and .cpp files

*****************************************************************/
// C++ code to implement an ATM and
// its basic functions
#include <fstream>
#include <iostream>
#include <limits>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

#ifndef Included_PrePaidCard

#define Included_PrePaidCard

// Class PrePaidCard to get user and Card details
class PrePaidCard {
private:

    int card_ID;
    int ccv;
    int user_ID;
    int pin;
    int balance = 0;
    int limit_negative = 3000;
    int interest_negative = 0.1;
    time_t last_login;
    int number_failed_login;
    char username[30];
    int password;
    
  
public:
    void setLastLogin (); //datetime
    string getLastLogin (); //datetime
    char* getUsername();
    double getBalance();
    void setBalance(double);
    double getLimit();
    int getPasswords();
    int getClient_id();
    void getData();
    void showData();
    void setPassword(int);
    void setPin(int);
    
};

#endif
