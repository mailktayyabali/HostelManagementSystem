#include "Validate.h"
#include <iostream>
#include <regex>

using namespace std;

int getValidatedInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (!cin.fail()) {
            cin.ignore(1000, '\n');
            return value;
        } else {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Please enter an integer.\n";
        }
    }
}

string getValidatedString(const string& prompt) {
    string value;
    while (true) {
        cout << prompt;
        getline(cin >> ws, value);
        if (!value.empty()) return value;
        cout << "Input cannot be empty. Try again.\n";
    }
}

string getValidatedCNIC(const string& prompt) {
    string cnic;
    regex pattern(R"(\d{5}-\d{7}-\d{1})");
    while (true) {
        cout << prompt;
        getline(cin >> ws, cnic);
        if (regex_match(cnic, pattern)) return cnic;
        cout << "Invalid CNIC format. Correct format: 12345-1234567-1\n";
    }
}

string getValidatedPhone(const string& prompt) {
    string phone;
    regex pattern(R"(03\d{9})");
    while (true) {
        cout << prompt;
        getline(cin >> ws, phone);
        if (regex_match(phone, pattern)) return phone;
        cout << "Invalid phone number. Must start with 03 and have 11 digits total.\n";
    }
}
