# 🔐 Password Manager

A simple C++ project to manage user credentials with basic encryption and file storage.

## Features
- Register, login, logout
- Add, update, delete, search, display users
- Save/load data from file
- XOR-based encrypt/decrypt

## Structure
- **User struct**: `userName`, `password`, `accountName`
- **PasswordManager class**: handles authentication, CRUD, file I/O, encryption

## 🚀 How to Run

1. Clone the repository:
   ```bash
   git clone https://github.com/devkantgupta01/PasswordManager.git
   cd PasswordManager



## Usage
```bash
g++ -std=c++17 main.cpp -o password_manager
./PasswordManager