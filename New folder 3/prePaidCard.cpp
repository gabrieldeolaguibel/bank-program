/*****************************************************************
NAME: Roger Castañer
ORGN: BCSAI-COMPUTER PROGRAMMING 1 22-23, IE University
FILE: prePaidCard.cpp
V1.0 Nov 19th 2022  Split the whole Original File in .h and .cpp files
*****************************************************************/
#include "prePaidCard.h"
//getters and setters
void PrePaidCard::setLastLogin() { last_login = time(0); }

string PrePaidCard::getLastLogin() {
  char *dt = ctime(&last_login); // convert in string form
  return dt;
}

char *PrePaidCard::getUsername(void) {
  // Return username
  return username;
}

int PrePaidCard::getPasswords(void) {
  // Return the password
  return password;
}

int PrePaidCard::getClient_id() { 
  return user_ID; 
  }

double PrePaidCard::getBalance() { 
  return balance; 
  }

void PrePaidCard::setBalance(double newBalance) { 
  balance = newBalance; 
  }

double PrePaidCard::getLimit() { 
  return limit_negative; 
  }

void PrePaidCard::setPassword(int newPassword) { 
  password = newPassword; 
  }

 

// Function to get the user's data
void PrePaidCard::getData(void) {
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "\nEnter username:"; // Setting the user's username
  cin.getline(username, 30);

  cout << "\nEnter 4-digit password:"; // Setting password
  cin >> password;
  
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "\nEnter initial balance:"; // Setting initial balance for the user
  cin >> balance;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "\nEnter pin:"; // Setting the user's PIN
  cin >> pin;

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cout << "\nEnter card id:"; // Setting the user's card ID
  cin >> card_ID;

  user_ID = card_ID; // Specifying that the user_ID = card_ID
  
  setLastLogin();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

// Function displaying the collected data
void PrePaidCard::showData(void) {
  cout << "Username:" << username << ", Password:" << password
       << ", Balance:" << balance << ", Last Login:" << getLastLogin() << endl;
}


