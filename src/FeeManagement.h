#ifndef FEEMANAGEMENT_H
#define FEEMANAGEMENT_H

#include <string>
#include <unordered_map>
#include "studentManagement.h"
#include "../Database/json.hpp"  // JSON header

using namespace std;
using json = nlohmann::json;

class FeeManagement {
private:
    struct FeeRecord {
        int totalFee;
        int paidFee;
        int securityFee;
        string date;
    };

    unordered_map<int, FeeRecord> feeTable;
    StudentManagement* sm;

public:
    FeeManagement(StudentManagement* sm);

    bool Add(int studentID, int totalFee, int paidFee, int securityFee, const string& date);
    bool Delete(int studentID);
    bool Update(int studentID, int totalFee, int paidFee, int securityFee, const string& date);
    bool Search(int studentID);
    bool CheckDue(int studentID);
    void View();

    // JSON File Handling
    void saveFeesToFile(const string& path);
    void loadFeesFromFile(const string& path);
    void updateFeeInFile(const string& path, int studentID);
    void deleteFeeFromFile(const string& path, int studentID);
};

#endif
