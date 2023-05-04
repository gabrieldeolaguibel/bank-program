#include "bankBranch.h"
#include "prePaidCard.h"

using namespace std;

// V3.0 Constructor. It opens by default a file called aaa.txt
BankBranch::BankBranch() {
  name = "aaa";
  file = "aaa.txt";
};

// V3.0 Constructor. It opens the file passed as argument
BankBranch::BankBranch(string name_branch) {
  name = name_branch;
  file = name_branch.append(".txt");
};

// global variable to keep track of amount users in blacklist
int blackListIndex = 0;

void BankBranch::loadBlackList() {
  ifstream file(name + "BL.txt");
  while (file >> blackList_clientsID[blackListIndex]) {
    blackListIndex++;
  }
  file.close();
}
//Store the blacklist into a file
void BankBranch::storeArrayIntoFile() {
  ofstream ofs;
  ofs.open(name + "BL.txt", ofstream::out | ofstream::trunc);
  ofs.close();

  ofstream file(name + "BL.txt");
  for (int i = 0; i < 10; i++) {
    file << blackList_clientsID[i] << endl;
  }
  file.close();
}
// function to check if a user is on the blacklist
bool BankBranch::isBlackListed(char *uname) {
  string tempS = uname;
  for (int i = 0; i < 10; i++) {
    if (blackList_clientsID[i] == tempS) {
      return true;
    }
  }
  return false;
}
//function to search the blacklist
int BankBranch::searchSpecificUserBL(char *uname) {
  string tempString = uname;
  for (int index = 0; index < blackListIndex; index++) {
    if (blackList_clientsID[index] == tempString) {
      return index;
    }
  }
  return -1;
}

// Function to delete a user from the Blacklist
int BankBranch::deleteUserFromBlackList(char *uname) {
  int index = searchSpecificUserBL(uname);
  if (index == -1) {
    cout << "User not found on black list";
    return -1;
  }
  for (int i = index; i < 10 - 1; i++) {
    blackList_clientsID[i] = blackList_clientsID[i + 1];
  }
  blackListIndex--;
  return 0;
}

string BankBranch::getName() { return name; }

// V2.0
void BankBranch::loadClients() {
  PrePaidCard a;

  ifstream file1;

  int i = 0;
  number_clients = 0; // V3 In case it is the first time we open the file

  // Open file in read mode
  file1.open(file, ios::in);
  if (!file1) {
    cout << "Error in opening file..";
  }

  // Read data from file
  file1.read((char *)&a, sizeof(a));
  while (!file1.eof()) {

    // Display data on monitor
    a.showData();
    client[i] = a;
    i++;
    file1.read((char *)&a, sizeof(a));
  }

  // Close the file
  file1.close();
  number_clients = i;
}

// Search user. Used by users
// V3. It returns the account_number if user\password are correct
int BankBranch::searchSpecificUser(char *uname, int pass) {
  for (int i = 1; i < number_clients; i++) {
    if (!strcmp(client[i].getUsername(), uname)) {
      if (client[i].getPasswords() == pass) {
        return i;
      }
    }
  }
  return -1; //-1 Password incorrect
}

// Search user. Used by Admins
// V3. It returns the account_number
int BankBranch::searchSpecificUser(char *uname) {
  for (int i = 0; i < number_clients; i++) {
    if (!strcmp(client[i].getUsername(), uname))
      return i;
  }
  return -1; //-1 No user found
}
//display user
void BankBranch::displayUser(char *uname) {
  int index = searchSpecificUser(uname);
  client[index].showData();
}

// V3
void BankBranch::setUserLoginDate(int found) { client[found].setLastLogin(); }

// Function to add user
int BankBranch::addUser() {
  PrePaidCard newPrepaidCard;
  newPrepaidCard.getData();
  client[number_clients] = newPrepaidCard;
  number_clients++;
  return 0;
}

// Function to delete the user
int BankBranch::deleteUser(char *uname) {
  int index = searchSpecificUser(uname);
  if (index == -1) {
    cout << "User not found" << endl;
    return -1;
  }
  for (int i = index; i < number_clients - 1; i++) {
    client[i] = client[i + 1];
  }
  number_clients--;
  return 0;
}
//function to add user to blacklist
int BankBranch::blacklistUser(char *uname) {
  int index = searchSpecificUser(uname);
  if (index == -1) {
    cout << "Client with that username not found";
    return -1;
  }
  blackList_clientsID[blackListIndex] = uname;
  deleteUser(uname); // delete them from the branch file
  return 0;
}

// Function to change the user's password
int BankBranch::changeUserPass(char *uname) {
  // check to see if the user exists in the branch
  int index = searchSpecificUser(uname);
  if (index == -1) {
    cout << "\nClient with that username not found";
    return -1;
  } else {
    // check to see if the new password is valid (has to be 4 characters long)
    bool checkPass = false;
    string tempPass;
    while (!checkPass) {
      cout << "\nEnter the new password: ";
      cin >> tempPass;

      if (tempPass.size() > 4) {
        cout << "\nInvalid password, it has to be 4 characters";
        continue;
      } else {
        // if its a valid password, change it 
        checkPass = true;
        client[index].setPassword(stoi(tempPass));
      }
    }
    return 0;
  }
}
// View Users
int BankBranch::viewallUsers() {
  if (number_clients == 0)
    cout << "We still don't have any client :-(\n";
  for (int i = 1; i < number_clients; i++) {
    client[i].showData();
  }
  return 0;
}
//Save clients to the branch text file
void BankBranch::saveClients() {
  fstream temp;
  if (number_clients == 0) // We still don't have any client
    return;

  temp.open("temp.txt", ios::out | ios::app);
  for (int i = 0; i < number_clients; i++) {
    temp.write((char *)&client[i], sizeof(client[i]));
  }
  // Close the file
  temp.close();
  remove(&file[0]);
  rename("temp.txt", &file[0]);
}

// Function to update userbalance (supports withdraw or deposit)
void BankBranch::updateUserBalance(char *uname, double amount,
                                   char operation = 'd') {
  // search to see if the user exists
  int index = searchSpecificUser(uname);
  // if user exists
  if (index != -1) {
    // get client balance
    double tempBalance = client[index].getBalance();
    // choose to deposit
    if (operation == 'd') {
      // deposit amount into client account
      client[index].setBalance(tempBalance + amount);
      // choose to withdraw
    } else {
      // check to see if the balance is higher than amount to withdraw
      if (tempBalance > amount) {
        // withdraw amount
        client[index].setBalance(tempBalance - amount);
        // check to see if the user is able to withdraw that much and not surpass the limit
      } else if (tempBalance < amount) {
        if ((amount - tempBalance) < client[index].getLimit()) {
          client[index].setBalance(tempBalance - amount);
        } 
      }
    }
  }
}
// function to display blacklist
int BankBranch::showblacklistUser(){
  // check to see if the blackList is empty
  if (blackListIndex == 0) {
    cout << "No users on the blacklist\n";
  }
  for (int i = 0; i < blackListIndex; i++) {
    cout << blackList_clientsID[i] << endl;
  }
  return 0;
}


// V3.0 Help Debug the code. Information for BankBranch Object (meant to be for testing)
int BankBranch::debug() {
  cout << "BankBranch Attributes\n";
  cout << "Name->" << name << " MAX_NUMBER_ACCOUNTS->" << MAX_NUMBER_ACCOUNTS
       << " number_clients->" << number_clients << " balance->" << balance
       << " file->" << file << endl;
  cout << "BlackList: " << endl;
  showblacklistUser();
  cout << "\n***All Users Information***\n";
  viewallUsers();
  return 0;
}

// function to show the balance of the branch
void BankBranch::showBankBalance() {
  // intialize tempBalanc to store the balance of all accounts
  double tempBalance = 0;
  // loop from index 1 to number_clients and add the balance to tempBalance
  for (int i = 1; i < number_clients; i++) {
    tempBalance += client[i].getBalance();
  }
  // display the branch balance
  cout << "The branch balance is: " << tempBalance << endl;
}
