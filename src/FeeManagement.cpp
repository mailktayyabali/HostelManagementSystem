#include "FeeManagement.h"
#include <iostream>
#include <fstream>

using namespace std;
using json = nlohmann::json;

FeeManagement::FeeManagement(StudentManagement* sm) {
    this->sm = sm;
}

bool FeeManagement::Add(int studentID, int totalFee, int paidFee, int securityFee, const string& date) {
    if (!sm->exists(studentID)) {
        cout << "Student does not exist!\n";
        return false;
    }
    if (feeTable.find(studentID) != feeTable.end()) {
        cout << "Fee record already exists!\n";
        return false;
    }
    feeTable[studentID] = { totalFee, paidFee, securityFee, date };
    cout << "Fee record added.\n";
    return true;
}

bool FeeManagement::Delete(int studentID) {
    if (feeTable.erase(studentID)) {
        cout << "Record deleted.\n";
        return true;
    }
    cout << "No record found to delete.\n";
    return false;
}

bool FeeManagement::Update(int studentID, int totalFee, int paidFee, int securityFee, const string& date) {
    auto it = feeTable.find(studentID);
    if (it != feeTable.end()) {
        it->second = { totalFee, paidFee, securityFee, date };
        cout << "Record updated.\n";
        return true;
    }
    cout << "Record not found.\n";
    return false;
}

bool FeeManagement::Search(int studentID) {
    auto it = feeTable.find(studentID);
    if (it != feeTable.end()) {
        cout << "Student ID: " << studentID << "\n"
             << "Total: " << it->second.totalFee << ", Paid: " << it->second.paidFee
             << ", Security: " << it->second.securityFee << ", Date: " << it->second.date << endl;
        return true;
    }
    cout << "No fee record found.\n";
    return false;
}

bool FeeManagement::CheckDue(int studentID) {
    auto it = feeTable.find(studentID);
    if (it != feeTable.end()) {
        int due = it->second.totalFee - it->second.paidFee;
        cout << "Due amount: " << due << endl;
        return true;
    }
    cout << "No record found.\n";
    return false;
}

void FeeManagement::View() {
    if (feeTable.empty()) {
        cout << "No records to display.\n";
        return;
    }

    for (const auto& pair : feeTable) {
        cout << "\nStudent ID: " << pair.first
             << "\nTotal Fee: " << pair.second.totalFee
             << "\nPaid Fee: " << pair.second.paidFee
             << "\nSecurity Fee: " << pair.second.securityFee
             << "\nDate: " << pair.second.date << "\n";
    }
}

// ====================== JSON FUNCTIONS ======================

void FeeManagement::saveFeesToFile(const string& path) {
    json jArray = json::array();
    for (const auto& pair : feeTable) {
        json j;
        j["studentID"] = pair.first;
        j["totalFee"] = pair.second.totalFee;
        j["paidFee"] = pair.second.paidFee;
        j["securityFee"] = pair.second.securityFee;
        j["date"] = pair.second.date;
        jArray.push_back(j);
    }

    ofstream outFile(path);
    if (outFile.is_open()) {
        outFile << jArray.dump(4);
        outFile.close();
        cout << "Fee records saved to " << path << endl;
    } else {
        cout << "❌ Failed to open file for saving!" << endl;
    }
}

void FeeManagement::loadFeesFromFile(const string& path) {
    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << "No saved fee data found." << endl;
        return;
    }

    json jArray;
    inFile >> jArray;
    inFile.close();

    for (const auto& j : jArray) {
        FeeRecord record;
        int id = j["studentID"];
        record.totalFee = j["totalFee"];
        record.paidFee = j["paidFee"];
        record.securityFee = j["securityFee"];
        record.date = j["date"];
        feeTable[id] = record;
    }

    cout << "Fee records loaded from " << path << endl;
}

void FeeManagement::updateFeeInFile(const string& path, int studentID) {
    ifstream inFile(path);
    if (!inFile.is_open()) return;

    json jArray;
    inFile >> jArray;
    inFile.close();

    for (auto& j : jArray) {
        if (j["studentID"] == studentID) {
            FeeRecord rec = feeTable[studentID];
            j["totalFee"] = rec.totalFee;
            j["paidFee"] = rec.paidFee;
            j["securityFee"] = rec.securityFee;
            j["date"] = rec.date;
            break;
        }
    }

    ofstream outFile(path);
    outFile << jArray.dump(4);
    outFile.close();
    cout << "Fee record updated in file." << endl;
}

void FeeManagement::deleteFeeFromFile(const string& path, int studentID) {
    ifstream inFile(path);
    if (!inFile.is_open()) return;

    json jArray;
    inFile >> jArray;
    inFile.close();

    for (auto it = jArray.begin(); it != jArray.end(); ++it) {
        if ((*it)["studentID"] == studentID) {
            jArray.erase(it);
            break;
        }
    }

    ofstream outFile(path);
    outFile << jArray.dump(4);
    outFile.close();
    cout << "Fee record deleted from file." << endl;
}
