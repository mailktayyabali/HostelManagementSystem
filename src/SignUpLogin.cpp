#include "SignUpLogin.h"
#include <iostream>
#include <conio.h>

using namespace std;

SignUpLogin::SignUpLogin() {
    userCount = 0;
}

bool SignUpLogin::usernameExists(const string& uname) {
    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == uname)
            return true;
    }
    return false;
}

bool SignUpLogin::isValidPassword(const string& pwd) {
    if (pwd.length() < 8) return false;
    for (char ch : pwd) {
        if (!isalnum(ch)) return true; 
    }
    return false;
}

string SignUpLogin::getMaskedPassword() {
    string pwd;
    char ch;
    while (true) {
        ch = _getch();
        if (ch == 13) break; 
        else if (ch == 8) {  
            if (!pwd.empty()) {
                cout << "\b \b";
                pwd.pop_back();
            }
        } else {
            pwd.push_back(ch);
            cout << '*';
        }
    }
    cout << endl;
    return pwd;
}

void SignUpLogin::SignUp() {
    if (userCount == MAX_USERS) {
        cout << "User limit reached!\n";
        return;
    }

    string uname, pwd, email, phone;
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, uname);

    if (usernameExists(uname)) {
        cout << "Username already exists! Try a different one.\n";
        return;
    }

    while (true) {
        cout << "Enter password (min 8 chars, at least one special character): ";
        pwd = getMaskedPassword();
        if (isValidPassword(pwd)) break;
        else cout << "Password does not meet requirements. Try again.\n";
    }

    cout << "Enter email: ";
    getline(cin, email);
    cout << "Enter phone number: ";
    getline(cin, phone);

    usernames[userCount] = uname;
    passwords[userCount] = pwd;
    emails[userCount] = email;
    phones[userCount] = phone;
    userCount++;

    cout << "Sign up successful!\n";
}

bool SignUpLogin::Login() {
    string uname, pwd;
    cout << "Enter username: ";
    cin.ignore();
    getline(cin, uname);
    cout << "Enter password: ";
    pwd = getMaskedPassword();

    for (int i = 0; i < userCount; i++) {
        if (usernames[i] == uname && passwords[i] == pwd) {
            cout << "Login successful!\n";
            return true;
        }
    }
    cout << "Invalid credentials!\n";
    return false;
}


// int main() {
//     SignUpLogin system;
//     int choice;

//     while (true) {
//         cout << "\n--- MENU ---\n";
//         cout << "1. Sign Up\n";
//         cout << "2. Login\n";
//         cout << "3. Exit\n";
//         cout << "Enter your choice: ";
//         cin >> choice;
//         cin.ignore();  

//         switch (choice) {
//             case 1:
//                 system.SignUp();
//                 break;
//             case 2:
//                 system.Login();
//                 break;
//             case 3:
//                 cout << "Exiting...\n";
//                 return 0;
//             default:
//                 cout << "Invalid choice! Try again.\n";
//         }
//     }

//     return 0;
// }
