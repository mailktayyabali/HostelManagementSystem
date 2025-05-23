/*header guards(Matlab,agar ye file multiple baar include ho jaye 
toh compiler ko sirf ek baar hi is file ko consider karna hai, taake errors na hon.) */
#ifndef FEEMANAGEMENT_H 
#define FEEMANAGEMENT_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class FeeRecord {
public:
    int studentID;
    string studentName;
    int totalFee;
    int feePaid;
    string feeDue;  // "Due" or "Cleared"
    int securityFee;
    vector<string> paymentDates;

    // Constructor
    FeeRecord(int id, string name, int total, int paid, int security, string date);
    void displayFeeRecord();
};
// FeeNode class to represent each node in the BST
class FeeNode {
public:
    FeeRecord* record;
    FeeNode* left;
    FeeNode* right;

    //Node Constructor
    FeeNode(FeeRecord* rec);
};
// FeeManagement class to manage the BST
class FeeManagement {
private:
    FeeNode* root;

    // Private methods for BST operations
    FeeNode* insert(FeeNode* node, FeeRecord* rec);
    FeeNode* search(FeeNode* node, int id);
    FeeNode* findMin(FeeNode* node);
    FeeNode* remove(FeeNode* node, int id);
    void inorder(FeeNode* node);

public:
    // Constructor
    FeeManagement();

    void Add(int id, string name, int totalFee, int paid, int securityFee, string date);
    void Delete(int id);
    void Update(int id, int totalFee);
    void Search(int id);
    void checkDue(int studentID);
    void displayAllFeeRecords();
};

#endif //header guards end
