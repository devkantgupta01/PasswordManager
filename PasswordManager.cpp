// 08-12-2025
#include<iostream>
#include<vector>
#include<fstream>
#include<vector>
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