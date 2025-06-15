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
            cin.ignore(1000, '\n'); // clear leftover newline
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
    regex pattern(R"(^[A-Za-z\s]+$)"); // letters and spaces only
    while (true) {
        cout << prompt;
        getline(cin, value);  // no cin.ignore() here
        if (!value.empty() && regex_match(value, pattern)) return value;
        cout << "Invalid input. Only letters and spaces are allowed. Try again.\n";
    }
}

string getValidatedCNIC(const string& prompt) {
    string cnic;
    regex pattern(R"(^\d{5}-\d{7}-\d{1}$)");
    while (true) {
        cout << prompt;
        getline(cin, cnic);  // no cin.ignore() here
        if (regex_match(cnic, pattern)) return cnic;
        cout << "Invalid CNIC format. Correct format: 12345-1234567-1\n";
    }
}

string getValidatedPhone(const string& prompt) {
    string phone;
    regex pattern(R"(^03\d{9}$)");
    while (true) {
        cout << prompt;
        getline(cin, phone);  // no cin.ignore() here
        if (regex_match(phone, pattern)) return phone;
        cout << "Invalid phone number. Must start with 03 and have 11 digits total.\n";
    }
}

std::string getValidatedDate(const std::string& prompt) {
    std::string date;
    // Match formats like 01-01-2025 or 31-12-2023
    std::regex pattern(R"(^(0[1-9]|[12][0-9]|3[01])-(0[1-9]|1[0-2])-(20\d{2})$)");
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, date);  // no cin.ignore() here
        if (regex_match(date, pattern)) return date;
        std::cout << "Invalid date format. Please use DD-MM-YYYY (e.g., 15-06-2025).\n";
    }
}
