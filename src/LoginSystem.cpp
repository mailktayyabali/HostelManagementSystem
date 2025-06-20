#include "LoginSystem.h"
#include "Animation.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <conio.h> // For _getch() — password masking on Windows

string getHiddenPassword() {
    string password;
    char ch;
    while ((ch = _getch()) != '\r') { // '\r' is Enter
        if (ch == '\b') { // Handle backspace
            if (!password.empty()) {
                cout << "\b \b";
                password.pop_back();
            }
        } else if (isprint(ch)) {
            password += ch;
            cout << '*';
        }
    }
    cout << endl;
    return password;
}

bool LoginSystem::adminExists() {
    ifstream file(filename);
    if (!file.is_open()) return false;

    json adminData;
    try {
        file >> adminData;
    } catch (...) {
        return false;  // JSON error or empty file
    }

    return adminData.contains("username") && adminData.contains("password") &&
           !adminData["username"].get<string>().empty() &&
           !adminData["password"].get<string>().empty();
}

void LoginSystem::registerAdmin() {
    string username, password;
    cout << "\t\t================================\n";
    cout << "\t\t||  Admin Registration        ||\n";
    cout << "\t\t================================\n";

    
    // Username validation
    do {
        cout << "Enter admin username: ";
        getline(cin, username);
        cin.ignore(); // Clear buffer before input
        if (username.empty()) {
            cout << "Username cannot be empty.\n";
        }
    } while (username.empty());

    // Password validation and masking
    do {
        cout << "Enter admin password (min 5 characters): ";
        password = getHiddenPassword();

        if (password.length() < 5) {
            cout << "Password too short! Must be at least 5 characters.\n";
        }
    } while (password.length() < 5);

    json adminData;
    adminData["username"] = username;
    adminData["password"] = password;

    ofstream outFile(filename);
    outFile << adminData.dump(4); // Pretty print JSON
    outFile.close();

    cout << "Admin registered successfully!\n";
    cout << "\t\t================================\n";
    system("cls");
}

bool LoginSystem::login() {
    if (!adminExists()) {
        cout << "No admin registered.\n";
        return false;
    }

    string username, password;
    cout << "\t\t================================\n";
    cout << "\t\t        -- Admin Login --       \n";
    cout << "\t\t================================\n";

    
    // Username input
    do {
        cout << "Enter username: ";
        getline(cin, username);
        cin.ignore(); // Clear buffer before input
        if (username.empty()) {
            cout << "Username cannot be empty.\n";
        }
    } while (username.empty());

    // Password input
    do {
        cout << "Enter password: ";
        password = getHiddenPassword();
        if (password.empty()) {
            cout << "Password cannot be empty.\n";
        }
    } while (password.empty());

    return validateCredentials(username, password);
}

bool LoginSystem::validateCredentials(const string& username, const string& password) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Admin file missing.\n";
        return false;
    }

    json adminData;
    inFile >> adminData;

    if (adminData["username"] == username && adminData["password"] == password) {
        system("cls");
        Animation::typeEffect("\n\t\tWelcome to Hostel Management System", 30);
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    } else {
        cout << "Invalid credentials.\n";
        return false;
    }
}
