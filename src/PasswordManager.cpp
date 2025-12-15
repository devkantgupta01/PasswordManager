// 08-12-2025
#include<iostream>
#include<vector>
#include<fstream>
#include<vector>
#include "colors.h"
using namespace std;

struct User{
    string userName;
    string password;
    string accountName;
};

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

void PasswordManager::saveToFile(){
    ofstream file(LoginUserName + ".txt");
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
    if(file.is_open()){
        getline(file, LoginUserName);
        getline(file, LoginPassword);
        User user;
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

        cin >> choice;
        cin.ignore();
        system("clear");
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
    cout<<"Registering a new user..."<<endl;
    cout<<"Enter username : ";
    getline(cin, inputUserName);
    cout<<"Enter password :";
    getline(cin, inputPassword);

    // check if the file already exists
    ifstream file(inputUserName + ".txt");
    if(file.is_open()){
        cout<<"Username already exitst. Please choose a different username."<<endl;
        file.close();
    } else {
        LoginUserName = inputUserName;
        LoginPassword = inputPassword;
        saveToFile();
        cout<<"User registered successfully!"<<endl;
        file.close();
    }
}

void PasswordManager::login(){
    string inputUserName;
    string inputPassword;
    cout<<"Loggin in..."<<endl;
    cout<<"Enter username :";
    getline(cin, inputUserName);
    ifstream file(inputUserName + ".txt");

    if(file.is_open()){
        file.close();
        LoginUserName = inputUserName;
        loadFromFile();
        cout<<"Enter password :";
        getline(cin, inputPassword);

        if(inputPassword == LoginPassword){
            cout<<"Login successful!" <<endl;
            // file.close();
            mainMenu();
        }
        else{
            cout<<"Incorrect password. Please try again. "<<endl;
            file.close();
        }
    }
    else{
        cout<<"Username not found. Please register first. "<<endl;
    }
}

void PasswordManager::mainMenu(){
    int choice;

    do {
        system("clear");  // or "cls" for Windows

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
        cin >> choice;
        cin.ignore();

        system("clear");
      
        switch(choice){
            case 1: addUser(); break;
            case 2: deleteUser(); break;
            case 3: updateUser(); break;
            case 4: displayUser(); break;
            case 5: searchUser(); break;
            case 6: logout(); break;
            default:
                cout << RED << "Invalid choice! Please try again...\n" << RESET;
        }
    } while (choice != 6);
}

void PasswordManager::addUser(){
    User newUser;
    cout << "Adding a new user..." << endl;
    cout << "Enter Username : ";
    getline(cin, newUser.userName);
    cout << "Enter password :";
    getline(cin, newUser.password);
    cout << "Enter account name : ";
    getline(cin, newUser.accountName);

    listOfUsers.push_back(newUser);
    saveToFile();
    cout << "User added successfully!" << endl;
}

void PasswordManager::deleteUser(){
    string userName;
    bool found = true;
    cout << "Deleting a user..." << endl;
    cout << "Enter username to delete : ";
    getline(cin, userName);

    for (auto it = listOfUsers.begin(); it != listOfUsers.end(); ++it){
        if(it->userName == userName){
            listOfUsers.erase(it);
            found = false;
            cout << "User deleted successfully!" << endl;
        }
    }
    if(found){
        cout << "User not found " << endl;
    }
}

void PasswordManager::updateUser(){
    string userName;
    cout << "Updating a user..." << endl;
    cout << "Enter username to update : ";
    getline(cin, userName);
    bool found = true;

    for(auto &user : listOfUsers){
        if(user.userName == userName){
            found = false;
            cout << "Enter new password :";
            getline(cin, user.password);
            cout << "User updated successfully" << endl;
        }
    }
    if(found){
        cout << "user not found " << endl;
    }
}