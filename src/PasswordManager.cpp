// 08-12-2025
#include<iostream>
#include<vector>
#include<fstream>
#include<vector>
#include<limits>
#include "colors.h"
using namespace std;

struct User{
    string userName;
    string password;
    string accountName;
};

ostream& operator<<(ostream& out, const User& Data){
    out<<"-------------------------------------"<<endl;
    out<<"User Name          :"<<Data.userName<<endl;
    out<<"Password           :"<<Data.password<<endl;
    out<<"Account Name       :"<<Data.accountName<<endl;
    return out;
}

class PasswordManager{
    private:
        string LoginUserName;
        string LoginPassword;
        vector<User> listOfUsers;
        ifstream file;

    public:
        void saveToFile();
        void loadFromFile();
        void mainMenu();
        void addUser();
        void deleteUser();
        void updateUser();
        void displayUser();
        void searchUser();
        void xorEncryptDecrypt(string &data, const string &key);
        void LoginMainMenu();
        void registerUser();
        void login();
        void logout();
};

void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void pauseScreen(){
    cout << CYAN << "\n--------------------------------------------\n" << RESET;
    cout << BOLD << "   Press ENTER to continue..." << RESET;
    cout << CYAN << "\n--------------------------------------------\n" << RESET;
    cin.get();
}



void PasswordManager::saveToFile(){
    ofstream file("User_Details/" + LoginUserName + ".txt");
    if(file.is_open()){
        file<<LoginUserName<<"\n";
        file<<LoginPassword<<"\n";
        for(const auto& user : listOfUsers){
            file<<user.userName<<"\n";
            file<<user.password<<"\n";
            file<<user.accountName<<"\n";
        }
        file.close();
    } else{
        cout<<"Unable to open file for writing!!!"<<endl;
    }
}

void PasswordManager::loadFromFile(){
    // file.open(LoginUserName + ".txt");
    ifstream file("User_Details/" + LoginUserName + ".txt");

    if(file.is_open()){
        getline(file, LoginUserName);
        getline(file, LoginPassword);

        User user;
        listOfUsers.clear();

        while(getline(file, user.userName) &&
              getline(file, user.password) &&
              getline(file, user.accountName))
              {
                listOfUsers.push_back(user);
              }
              file.close();
    }
    else{
        cout<<"Unable to open file for reading!!!"<<endl;
    }
}

void PasswordManager::LoginMainMenu(){
    int choice;
    do{
        cout << CYAN << "\n============================================\n" << RESET;
        cout << BOLD << "              PASSWORD MANAGER\n" << RESET;
        cout << CYAN << "============================================\n\n" << RESET;

        cout << BOLD << "                   MAIN MENU\n" << RESET;
        cout << "--------------------------------------------\n";
        cout << GREEN << "  [1] Register\n" << RESET;
        cout << BLUE  << "  [2] Login\n"  << RESET;
        cout << YELLOW << "  [3] Exit\n"  << RESET;
        cout << "--------------------------------------------\n";
        cout << BOLD << "Please Select an option: " << RESET;

        // cin >> choice;
        // cin.ignore();

        // clearScreen();

        if (!(cin >> choice)){   //If the input cannot be parsed into the choice (e.g., choice is an int but the user types "abc", a", "&*", etc), then cin enters a fail state.
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); //flush buffer
            cout<< RED << "Invalid input! Please enter a number. \n"<< RESET;

            pauseScreen();
            clearScreen();

            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clearScreen();

        switch(choice)
        {
            case 1:
                registerUser();
                break;
            case 2:
                login();
                break;
            case 3:
                cout<<GREEN<<"Exiting the program..."<<RESET;
                break;
            default:
                cout<<RED<<"Invalid choice, Please try again...!!!"<<RESET;
        }
    } while (choice != 3);
}

void PasswordManager::registerUser(){
    string inputUserName;
    string inputPassword;

    cout << CYAN << "\n============================================\n" << RESET;
    cout << BOLD << "           USER REGISTRATION\n" << RESET;
    cout << CYAN << "============================================\n\n" << RESET;

    cout << "Enter username : ";
    getline(cin, inputUserName);

    cout << "Enter password : ";
    getline(cin, inputPassword);

    pauseScreen();
    clearScreen();
  

    // check if the file already exists
    ifstream file(inputUserName + ".txt");
    if(file.is_open()){
        cout << RED
             << "\n[!] Username already exists.\n"
             << "    Please choose a different username.\n"
             << RESET;
        file.close();
    } 
    else {
        LoginUserName = inputUserName;
        LoginPassword = inputPassword;
        saveToFile();
        cout << GREEN
             << "\n[+] User registered successfully!\n"
             << RESET;
        file.close();
    }

    cout << CYAN << "\n--------------------------------------------\n" << RESET;
}

void PasswordManager::login(){
    string inputUserName;
    string inputPassword;

    cout << CYAN << "\n============================================\n" << RESET;
    cout << BOLD << "                USER LOGIN\n" << RESET;
    cout << CYAN << "============================================\n\n" << RESET;

    cout << "Enter username : ";
    getline(cin, inputUserName);

    ifstream checkFile("User_Details/" + inputUserName + ".txt");

    if(checkFile.is_open()){
        checkFile.close();

        LoginUserName = inputUserName;
        loadFromFile();

        cout << "Enter password : ";
        getline(cin, inputPassword);

        if(inputPassword == LoginPassword){
            cout << GREEN << "\n[+] Login successful!\n" << RESET;
            mainMenu();
        }
        else{
            cout << RED << "\n[!] Incorrect password. Please try again.\n" << RESET;
        }
    }
    else{
        cout << YELLOW
             << "\n[!] Username not found.\n"
             << "    Please register first.\n"
             << RESET;
    }

    cout << CYAN << "\n--------------------------------------------\n" << RESET;
}

void PasswordManager::mainMenu(){
    int choice;

    do {
        clearScreen();  // or "cls" for Windows

        cout << BLUE << "=====================================\n" << RESET;
        cout << CYAN << "        PASSWORD MANAGER MENU        \n" << RESET;
        cout << BLUE << "=====================================\n" << RESET;

        cout << YELLOW << "1. Add User\n";
        cout << "2. Delete User\n";
        cout << "3. Update User\n";
        cout << "4. Display Users\n";
        cout << "5. Search User\n";
        cout << "6. Logout\n" << RESET;

        cout << GREEN << "\nPlease select an option: " << RESET;
        // cin >> choice;
        // cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if(!(cin>>choice)){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout<< RED << "invalid input! Please enter a number. \n"<< RESET;
            pauseScreen();
            continue;
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clearScreen();
      
        switch(choice){
            case 1: addUser(); break;
            case 2: deleteUser(); break;
            case 3: updateUser(); break;
            case 4: displayUser(); break;
            case 5: searchUser(); break;
            case 6: logout();  break;
            default:
                cout << RED << "Invalid choice! Please try again...\n" << RESET;
        }
        if(choice != 6){
            pauseScreen();
        }
    } while (choice != 6);
}

void PasswordManager::addUser(){
    User newUser;

    cout << CYAN << "\n============================================\n" << RESET;
    cout << BOLD << "              ADD NEW USER\n" << RESET;
    cout << CYAN << "============================================\n\n" << RESET;

    cout << "Enter Username       : ";
    getline(cin, newUser.userName);

    cout << "Enter password       : ";
    getline(cin, newUser.password);

    cout << "Enter account name   : ";
    getline(cin, newUser.accountName);

    listOfUsers.push_back(newUser);
    saveToFile();

    cout << GREEN << "\n[+] User added successfully!\n" << RESET;
    cout << CYAN << "\n--------------------------------------------\n" << RESET;
}

void PasswordManager::deleteUser(){
    string userName;
    bool found = true;

    cout << CYAN << "\n============================================\n" << RESET;
    cout << BOLD << "             DELETE USER\n" << RESET;
    cout << CYAN << "============================================\n\n" << RESET;

    cout << "Enter username to delete : ";
    getline(cin, userName);

    for (auto it = listOfUsers.begin(); it != listOfUsers.end(); ++it){
        if(it->userName == userName){
            listOfUsers.erase(it);
            found = true;
            cout << GREEN << "\n[+] User deleted successfully!\n" << RESET;
            break;
        }
    }

    if(!found){
        cout << RED << "\n[!] User not found.\n" << RESET;
    }

    cout << CYAN << "\n--------------------------------------------\n" << RESET;
}

void PasswordManager::updateUser(){
    string userName;
    bool found = false;

    cout << CYAN << "\n============================================\n" << RESET;
    cout << BOLD << "             UPDATE USER\n" << RESET;
    cout << CYAN << "============================================\n\n" << RESET;

    cout << "Enter username to update : ";
    getline(cin, userName);

    for(auto &user : listOfUsers){
        if(user.userName == userName){
            cout << "Enter new password : ";
            getline(cin, user.password);
            found = true;
            cout << GREEN << "\n[+] User updated successfully!\n" << RESET;
            break;
        }
    }

    if(!found){
        cout << RED << "\n[!] User not found.\n" << RESET;
    }

    cout << CYAN << "\n--------------------------------------------\n" << RESET;
}

void PasswordManager::displayUser(){
    if(listOfUsers.empty()){
        cout << YELLOW << "\n[!] Database is empty.\n" << RESET;
        pauseScreen();
        return;
    }

    cout << CYAN << "\n============================================\n" << RESET;
    cout << BOLD << "           DISPLAYING ALL USERS\n" << RESET;
    cout << CYAN << "============================================\n" << RESET;

    for (const auto& user : listOfUsers){
        cout << user;
    }

    cout << CYAN << "\n--------------------------------------------\n" << RESET;
    // pauseScreen();
}

void PasswordManager::searchUser(){
    // cout << YELLOW << "DEBUG username = " << LoginUserName << "j\n" << RESET;

    string userName;
    bool found = false;

    cout << CYAN << "\n============================================\n" << RESET;
    cout << BOLD << "             SEARCH USER\n" << RESET;
    cout << CYAN << "============================================\n\n" << RESET;

    cout << "Enter username to search : ";
    getline(cin, userName);

    for(const auto& User : listOfUsers){
        if(User.userName == userName){
            cout << GREEN << "\n[+] User found:\n" << RESET;
            cout << User;
            found = true;
            break;
        }
    }

    if(!found){
        cout << RED << "\n[!] User not found.\n" << RESET;
    }

    cout << CYAN << "\n--------------------------------------------\n" << RESET;
    // pauseScreen();
}

void PasswordManager::logout(){

    cout<<"Logging out..."<<endl;
    saveToFile();
    LoginUserName = "";
    LoginPassword = "";
    listOfUsers.clear();
    cout<<"Logged out successfully!!!"<<endl;
}

int main(){
    PasswordManager PM;
    PM.LoginMainMenu();
    cout<<endl;
    return 0;
}