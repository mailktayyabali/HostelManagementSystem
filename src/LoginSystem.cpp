#include "LoginSystem.h"

bool LoginSystem::adminExists() {
    ifstream file(filename);
    return file.good() && file.peek() != ifstream::traits_type::eof(); // check if file exists and is not empty
}

void LoginSystem::registerAdmin() {
    string username, password;

    cout << "\n-- Admin Registration --\n";
    cin.ignore(); // clear any leftover input
    cout << "Enter admin username: ";
    getline(cin, username);  // handles spaces

    cout << "Enter admin password: ";
    getline(cin, password);  // handles spaces

    json adminData;
    adminData["username"] = username;
    adminData["password"] = password;

    ofstream outFile(filename);
    outFile << adminData.dump(4); // nicely formatted JSON
    outFile.close();

    cout << "✅ Admin registered successfully!\n";
}

bool LoginSystem::login() {
    if (!adminExists()) {
        cout << "❌ No admin registered.\n";
        return false;
    }

    string username, password;
    cin.ignore(); // clear leftover newline
    cout << "\n-- Admin Login --\n";
    cout << "Enter username: ";
    getline(cin, username);

    cout << "Enter password: ";
    getline(cin, password);

    return validateCredentials(username, password);
}

bool LoginSystem::validateCredentials(const string& username, const string& password) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "⚠️ Admin file missing.\n";
        return false;
    }

    json adminData;
    inFile >> adminData;

    if (adminData["username"] == username && adminData["password"] == password) {
        cout << "✅ Login successful. Welcome, Admin!\n";
        return true;
    } else {
        cout << "❌ Invalid credentials.\n";
        return false;
    }
}
