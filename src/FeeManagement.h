#ifndef FEEMANAGEMENT_H
#define FEEMANAGEMENT_H

#include <string>
#include <unordered_map>
using namespace std;

#include "studentManagement.h"

class FeeManagement {
private:
    struct FeeRecord {
        int totalFee;
        int paidFee;
        int securityFee;
        string date;
    };

    unordered_map<int, FeeRecord> feeTable;  // Hash table using student ID as key
    StudentManagement* sm;

public:
    FeeManagement(StudentManagement* sm);  // constructor with pointer

    bool Add(int studentID, int totalFee, int paidFee, int securityFee, const string& date);
    bool Delete(int studentID);
    bool Update(int studentID, int totalFee, int paidFee, int securityFee, const string& date);
    bool Search(int studentID);
    bool CheckDue(int studentID);
    void View();  // View all fee records
};

#endif
