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