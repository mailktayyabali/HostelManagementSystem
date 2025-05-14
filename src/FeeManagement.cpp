#include <iostream>
#include <vector>
#include <string>
using namespace std;

class FeeRecord {
public:
    int studentID;
    string studentName;
    int totalFee;
    int feePaid;
    string feeDue;
    int securityFee;
    vector<string> paymentDates;

    FeeRecord(int id, string name, int total, int paid, int security, string date) {
        studentID = id;
        studentName = name;
        totalFee = total;
        feePaid = paid;
        securityFee = security;
        feeDue = ((totalFee - feePaid) > 0) ? "Due" : "Cleared";
        paymentDates.push_back(date);
    }

    void displayFeeRecord() {
        cout << "\nStudent ID: " << studentID << endl;
        cout << "Student Name: " << studentName << endl;
        cout << "Total Fee: " << totalFee << endl;
        cout << "Fee Paid: " << feePaid << endl;
        cout << "Security Fee: " << securityFee << endl;
        cout << "Fee Due Status: " << feeDue << endl;
        cout << "Payment Dates: ";
        for (const string& date : paymentDates) {
            cout << date << " ";
        }
        cout << endl;
    }
};

class FeeManagement {
private:
    vector<FeeRecord> records;

public:
    void Add(int id, string name, int totalFee, int paid, int securityFee, string date) {
        records.push_back(FeeRecord(id, name, totalFee, paid, securityFee, date));
        cout << "Record added successfully.\n";
    }

    void Delete(int id) {
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].studentID == id) {
                records.erase(records.begin() + i);
                cout << "Record deleted successfully.\n";
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void Update(int id, int totalFee) {
        for (auto& rec : records) {
            if (rec.studentID == id) {
                rec.totalFee = totalFee;
                rec.feeDue = ((rec.totalFee - rec.feePaid) > 0) ? "Due" : "Cleared";
                cout << "Total fee updated.\n";
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void Search(int id) {
        for (auto& rec : records) {
            if (rec.studentID == id) {
                rec.displayFeeRecord();
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void View() {
        if (records.empty()) {
            cout << "No records found.\n";
            return;
        }
        for (auto& rec : records) {
            rec.displayFeeRecord();
            cout << "------------------------\n";
        }
    }

    void checkDue(int studentID) {
        for (auto& rec : records) {
            if (rec.studentID == studentID) {
                cout << "Fee Due Status for Student ID " << studentID << ": " << rec.feeDue << endl;
                return;
            }
        }
        cout << "Student not found.\n";
    }

    void displayAllFeeRecords() {
        View();
    }
};

