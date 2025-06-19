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
        cout << " Student does not exist!\n";
        return false;
    }
    if (feeTable[studentID].find(date) != feeTable[studentID].end()) {
        cout << " Fee record for this date already exists!\n";
        return false;
    }
    feeTable[studentID][date] = { totalFee, paidFee, securityFee, date };
    cout << " Fee record added for " << date << ".\n";
    return true;
}

bool FeeManagement::Delete(int studentID, const string& date) {
    if (feeTable.find(studentID) != feeTable.end() &&
        feeTable[studentID].find(date) != feeTable[studentID].end()) {
        feeTable[studentID].erase(date);
        cout << " Fee record deleted for " << date << ".\n";
        return true;
    }
    cout << " No fee record found for the given student and date.\n";
    return false;
}

bool FeeManagement::Update(int studentID, int totalFee, int paidFee, int securityFee, const string& date) {
    if (feeTable.find(studentID) != feeTable.end() &&
        feeTable[studentID].find(date) != feeTable[studentID].end()) {
        feeTable[studentID][date] = { totalFee, paidFee, securityFee, date };
        cout << " Fee record updated for " << date << ".\n";
        return true;
    }
    cout << " No record found to update.\n";
    return false;
}

bool FeeManagement::Search(int studentID) {
    if (feeTable.find(studentID) == feeTable.end() || feeTable[studentID].empty()) {
        cout << " No fee record found for this student.\n";
        return false;
    }

    cout << " Fee records for Student ID: " << studentID << "\n";
    for (const auto& [date, rec] : feeTable[studentID]) {
        cout << "   Date: " << date
             << " | Total: " << rec.totalFee
             << " | Paid: " << rec.paidFee
             << " | Security: " << rec.securityFee << "\n";
    }
    return true;
}

bool FeeManagement::CheckDue(int studentID, const string& date) {
    if (feeTable.find(studentID) != feeTable.end() &&
        feeTable[studentID].find(date) != feeTable[studentID].end()) {
        const FeeRecord& rec = feeTable[studentID][date];
        int due = rec.totalFee - rec.paidFee;
        cout << " Due amount for " << date << ": " << due << endl;
        return true;
    }
    cout << " No record found for given student and date.\n";
    return false;
}

void FeeManagement::View() {
    if (feeTable.empty()) {
        cout << "⚠️ No fee records to display.\n";
        return;
    }

    for (const auto& [studentID, dateMap] : feeTable) {
        cout << "\n🔹 Student ID: " << studentID << "\n";
        for (const auto& [date, rec] : dateMap) {
            cout << "   Date: " << date
                 << " | Total: " << rec.totalFee
                 << " | Paid: " << rec.paidFee
                 << " | Security: " << rec.securityFee << "\n";
        }
    }
}

void FeeManagement::saveFeesToFile(const string& path) {
    json jArray = json::array();

    for (const auto& [studentID, dateMap] : feeTable) {
        for (const auto& [date, rec] : dateMap) {
            json j;
            j["studentID"] = studentID;
            j["totalFee"] = rec.totalFee;
            j["paidFee"] = rec.paidFee;
            j["securityFee"] = rec.securityFee;
            j["date"] = date;
            jArray.push_back(j);
        }
    }

    ofstream outFile(path);
    if (outFile.is_open()) {
        outFile << jArray.dump(4);
        outFile.close();
        cout << " Fee records saved to file.\n";
    } else {
        cout << " Failed to open file for saving.\n";
    }
}

void FeeManagement::loadFeesFromFile(const string& path) {
    ifstream inFile(path);
    if (!inFile.is_open()) {
        cout << " No saved fee data found.\n";
        return;
    }

    json jArray;
    inFile >> jArray;
    inFile.close();

    for (const auto& j : jArray) {
        FeeRecord rec;
        int id = j["studentID"];
        string date = j["date"];
        rec.totalFee = j["totalFee"];
        rec.paidFee = j["paidFee"];
        rec.securityFee = j["securityFee"];
        rec.date = date;
        feeTable[id][date] = rec;
    }

    cout << " Fee records loaded from file.\n";
}

void FeeManagement::updateFeeInFile(const string& path, int studentID, const string& date) {
    ifstream inFile(path);
    if (!inFile.is_open()) return;

    json jArray;
    inFile >> jArray;
    inFile.close();

    for (auto& j : jArray) {
        if (j["studentID"] == studentID && j["date"] == date) {
            const FeeRecord& rec = feeTable[studentID][date];
            j["totalFee"] = rec.totalFee;
            j["paidFee"] = rec.paidFee;
            j["securityFee"] = rec.securityFee;
            break;
        }
    }

    ofstream outFile(path);
    outFile << jArray.dump(4);
    outFile.close();
    cout << " Fee record updated in file.\n";
}

void FeeManagement::deleteFeeFromFile(const string& path, int studentID, const string& date) {
    ifstream inFile(path);
    if (!inFile.is_open()) return;

    json jArray;
    inFile >> jArray;
    inFile.close();

    for (auto it = jArray.begin(); it != jArray.end(); ++it) {
        if ((*it)["studentID"] == studentID && (*it)["date"] == date) {
            jArray.erase(it);
            break;
        }
    }

    ofstream outFile(path);
    outFile << jArray.dump(4);
    outFile.close();
    cout << " Fee record deleted from file.\n";
}
