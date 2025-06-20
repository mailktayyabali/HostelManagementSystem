#include "LoginSystem.h"
#include "Animation.h"
#include <chrono>
#include <thread>
#include <cstdlib>
#include <conio.h> // at top

bool LoginSystem::adminExists() {
    ifstream file(filename);
    if (!file.is_open()) return false;

    json adminData;
    try {
        file >> adminData;
    } catch (...) {
        return false;  // JSON parsing failed
    }

    // Check if both keys exist and are not empty
    return adminData.contains("username") && adminData.contains("password") &&
           !adminData["username"].get<string>().empty() &&
           !adminData["password"].get<string>().empty();
}


void LoginSystem::registerAdmin() {
    string username, password;
    cout << "\t\t================================\n";
    cout << "\t\t||\tAdmin Registration    ";
    cout<<"||\n";
    cout << "\t\t================================\n";
    cout << "Enter admin username: ";
    cin.ignore(); // clear any leftover input
    getline(cin, username);  // handles spaces

    cout << "Enter admin password: ";
    getline(cin, password);  // handles spaces

    json adminData;
    adminData["username"] = username;
    adminData["password"] = password;

    ofstream outFile(filename);
    outFile << adminData.dump(4); // nicely formatted JSON
    outFile.close();

    cout << "Admin registered successfully!\n";
    cout << "\t\t================================\n";
    system("cls"); // clear screen after registration
}

bool LoginSystem::login() {
    if (!adminExists()) {
        cout << " No admin registered.\n";

        return false;
    }

    string username, password;
    cout <<"\t\t================================\n";
    cout << "\t\t\t-- Admin Login --\n";
    cout << "\t\t================================\n";
    cout << "\nEnter username: ";
    cin.ignore(); // clear leftover newline
    getline(cin, username);

    cout << "\nEnter password: ";
    getline(cin, password);

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
        Animation::typeEffect("\n\t\tWelcomme to Hostel Management System", 30);
        this_thread::sleep_for(chrono::milliseconds(1000));
        return true;
    } else {
        cout << " Invalid credentials.\n";
        return false;
    }
}
