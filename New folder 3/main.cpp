#include "bankBranch.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <string.h>
#include <unistd.h>

using namespace std;

void atmUser(string branch = "default") {
  BankBranch *activeBranch; // the branch the user/admin will work with
  char uname[30];           // username
  int pass, ch, ch1, ch2, found = 0;
  char depWith;      // deposit or withdraw variable
  double tempAmount; // temporary variable to store amount
  bool validOption = false;

  if (branch == "default") { // if no argument given
    const string branch1 = "madrid";
    const string branch2 = "segovia";

    int choice;
    cout << "Select the Branch that you would like to work on (the number):";
    cout << "\n1. aaa\n2. Madrid\n3. Segovia";
    cout << "\nChoose one:";
    while (!validOption) {
      cin >> choice;
      if (choice == 1) {
        BankBranch defaultBranch;
        activeBranch = &defaultBranch; // set the branch to aaa
        validOption = true;            // exit the while loop

      } else if (choice == 2) {
        BankBranch madridBranch(branch1);
        activeBranch = &madridBranch; // set the branch to madrid
        validOption = true;           // exit the while loop
      } else if (choice == 3) {
        BankBranch segoviaBranch(branch2);
        activeBranch = &segoviaBranch; // set the branch to segovia
        validOption = true;            // exit the while loop
      } else {
        cout << "Invalid option\nPlease select a valid branch\n";
        continue;
      }
    }
  } else { // if the argument is given
    BankBranch temp(branch);
    activeBranch = &temp;
  }

  activeBranch->loadClients();
  activeBranch->loadBlackList();
  // activeBranch->debug();


mainmenu:
  system("clear");
  cout << "\nWelcome to " << activeBranch->getName();
  cout << "\nLogin as: \n1. Admin\n2. User\n3. Exit"
       << "\nChoose one: ";
  cin >> ch;

  switch (ch) {
  case 1: // Log in as admin
  rerun:
    system("clear");
    cout << "\nEnter details to login as Admin\n";
    cout << "\nEnter password:";
    cin >> pass;
    if (pass == 1234) {
    admin: // Admin Profile Type Functionalities
      system("clear");
      cout << "\nWelcome to Admin menu";
      cout << "\n1. Add user\n2. Delete user\n3. View all users\n4. Add user "
              "to blacklist\n5. Delete user from backlist"
           << "\n6. View Blacklist"
           << "\n7. Change user pin"
           << "\n8. Make a deposit or withdraw for customer"
           << "\n9. View Branch balance"
           << "\n10. Exit";
      cout << "\nSelect one: ";
      cin >> ch1;
      switch (ch1) {
      case 1: // Adding a new Admin user
        activeBranch->addUser();
        goto admin;

      case 2: // Selecting username to be deleted by admin
        cout << "\nEnter the username to be deleted: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(uname, 30);
        activeBranch->deleteUser(uname);
        goto admin;

      case 3: // View all registered users
        activeBranch->viewallUsers();
        sleep(3);
        goto admin;

      case 4: // Blacklist a specific user
        cout << "\nEnter the username to be added to the blacklist: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(uname, 30);
        activeBranch->blacklistUser(uname);
        goto admin;

      case 5: // Removing a specific user from the blacklist
        cout << "\nEnter the username that you would like to remove from the "
                "blacklist: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(uname, 30);
        activeBranch->deleteUserFromBlackList(uname);
        goto admin;

      case 6: // Displayig users who are blaklisted
        cout << "\nBlackList: " << endl;
        activeBranch->showblacklistUser();
        sleep(3);
        goto admin;

      case 7: // for changing the user password/pin
        cout << "\nEnter the username of the account you want to change the "
                "pin: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.getline(uname, 30);
        activeBranch->changeUserPass(uname);
        goto admin;

      case 8: // make a deposit or withdraw for customer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\nEnter customer username:";
        cin.getline(uname, 30);
        found = activeBranch->searchSpecificUser(uname);
        validOption = false;
        while (!validOption) {
          cout << "Would you like to do  a deposit or a withdraw (type: d/w)";
          cin >> depWith;
          if (depWith == 'd' || depWith == 'w') {
            validOption = true;
            cout << "How much would you like to "
                 << ((depWith == 'd') ? "deposit\n" : "withdraw\n");
            cin >> tempAmount;
            activeBranch->updateUserBalance(uname, tempAmount, depWith);
          } else {
            cout << "Invalid option, please type (d/w)\n";
          }
        }
        sleep(3);
        goto admin;

      case 9: // Displaying the total Bank Balance for the specific branch
        activeBranch->showBankBalance();
        sleep(3);

      case 10:
        break;
      }
    } else { // if the admin password is not correct
      cout << "\nDetails are incorrect! Please try again";
      cin.get();
      goto rerun;
    }
    goto mainmenu;

  case 2: // Log in as user
    cout << "\nEnter details to login as User";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "\nEnter username:";
    cin.getline(uname, 30);

    if (activeBranch->isBlackListed(uname)) { // if the user is on the blacklist
      cout
          << "Sorry, you cannot access your account because you're blacklisted";
    } else { // if they're not on the blacklist
      cout << "\nEnter password:";
      cin >> pass;
      found = activeBranch->searchSpecificUser(uname, pass);
      if (found != -1) {
      user: // User Type Functionalities
        system("clear");
        activeBranch->setUserLoginDate(found);
        cout << "\nWelcome " << uname;
        cout << "\nWelcome to the user Menu";
        cout << "\n1. Deposit or Withdraw \n2. View "
                "Account \n3. Change Pin \n4. Exit \nEnter your choice:";
        cin >> ch2;

        switch (ch2) {
        case 1: // Ability to either deposit or withdraw a specific amount
          validOption = false;
          while (!validOption) {
            cout << "Would you like to do  a deposit or a withdraw (type: d/w)";
            cin >> depWith;
            if (depWith == 'd' || depWith == 'w') {
              validOption = true;
              cout << "How much would you like to "
                   << ((depWith == 'd') ? "deposit\n" : "withdraw\n");
              cin >> tempAmount;
              activeBranch->updateUserBalance(uname, tempAmount, depWith);
            } else {
              cout << "Invalid option, please type (d/w)\n";
            }
          }
          sleep(3);
          goto user;
        case 2: // Displaying user information
          activeBranch->displayUser(uname);
          sleep(4);
          goto user;
        case 3: // Ability for the user to change its password
          activeBranch->changeUserPass(uname);
          goto user;
        case 4:
          cout << "Thank you";
          break;
        }
      } else { // If the specified user does not exist, the following message
               // will be displayed:
        cout << "\nNo account found with username " << uname
             << ":(\nHit ENTER to continue ";
        cin.get();
      }
    }
    goto mainmenu;

  case 3: // If all user actions are successful, this message will display:
    cout << "\nThank you for banking with us ";
    activeBranch->saveClients();
    activeBranch->storeArrayIntoFile();
    cin.get();
    break;
  }
}

// Driver Code
int main(int argc, char **argv) {
  string activeBranch = "";
  if (argc == 2) {
    string temp = argv[1];
    if (temp == "aaa" || temp == "madrid" || temp == "segovia") {
      activeBranch = argv[1];
      atmUser(activeBranch);
    } else {
      cout << "Invalid branch (valid options: aaa || madrid || segovia";
    }
  } else {
    atmUser();
  }
  return 0;
}