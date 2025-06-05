#include "FeeManagement.h"
#include <iostream>
using namespace std;

FeeManagement::FeeManagement(StudentManagement* sm) {
    this->sm = sm;
}

bool FeeManagement::Add(int studentID, int totalFee, int paidFee, int securityFee, const string& date) {
    if (!sm->exists(studentID)) {
        cout << "Student does not exist!\n";
        return false;
    }
    FeeRecord record = { totalFee, paidFee, securityFee, date };
    feeTable[studentID] = record;
    cout << "Fee record added.\n";
    return true;
}

bool FeeManagement::Delete(int studentID) {
    if (!sm->exists(studentID)) {
        cout << "Student does not exist!\n";
        return false;
    }
    if (feeTable.erase(studentID)) {
        cout << "Record deleted.\n";
        return true;
    }
    cout << "No record found to delete.\n";
    return false;
}

bool FeeManagement::Update(int studentID, int totalFee, int paidFee, int securityFee, const string& date) {
    if (!sm->exists(studentID)) {
        cout << "Student does not exist!\n";
        return false;
    }
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
        cout << "Fee Record for Student ID: " << studentID << endl;
        cout << "Total: " << it->second.totalFee << ", Paid: " << it->second.paidFee
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