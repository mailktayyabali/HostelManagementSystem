// FeeManagement.cpp
#include "FeeManagement.h"
// Constructor for FeeRecord initializes the member variables
FeeRecord::FeeRecord(int id, string name, int total, int paid, int security, string date) {
    studentID = id;
    studentName = name;
    totalFee = total;
    feePaid = paid;
    securityFee = security;
    feeDue = ((totalFee - feePaid) > 0) ? "Due" : "Cleared";
    paymentDates.push_back(date);
}
// Function to display the fee record
void FeeRecord::displayFeeRecord() {
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
//when we create a new FeeNode, we need to pass a FeeRecord object to it
// FeeNode constructor initializes the record and sets left and right pointers to nullptr
FeeNode::FeeNode(FeeRecord* rec) {
    record = rec;
    left = right = nullptr;
}

FeeManagement::FeeManagement() {
    root = nullptr;
}
// Function to insert a new fee record into the BST
FeeNode* FeeManagement::insert(FeeNode* node, FeeRecord* rec) {
    if (node == nullptr) return new FeeNode(rec);
    if (rec->studentID < node->record->studentID)
        node->left = insert(node->left, rec);
    else
        node->right = insert(node->right, rec);
    return node;
}
// Function to search for a fee record by student ID
FeeNode* FeeManagement::search(FeeNode* node, int id) {
    if (node == nullptr || node->record->studentID == id) return node;
    if (id < node->record->studentID)
        return search(node->left, id);
    return search(node->right, id);
}
// Function to find the minimum value node in the BST
FeeNode* FeeManagement::findMin(FeeNode* node) {
    while (node && node->left != nullptr)
        node = node->left;
    return node;
}
// Function to remove a fee record from the BST
FeeNode* FeeManagement::remove(FeeNode* node, int id) {
    if (node == nullptr) return node;
    if (id < node->record->studentID)
        node->left = remove(node->left, id);
    else if (id > node->record->studentID)
        node->right = remove(node->right, id);
    else {
        if (node->left == nullptr) {
            FeeNode* temp = node->right;
            delete node;
            return temp;
        } else if (node->right == nullptr) {
            FeeNode* temp = node->left;
            delete node;
            return temp;
        } else {
            FeeNode* temp = findMin(node->right);
            node->record = temp->record;
            node->right = remove(node->right, temp->record->studentID);
        }
    }
    return node;
}
// Function to perform inorder traversal of the BST and display all fee records
void FeeManagement::inorder(FeeNode* node) {
    if (node != nullptr) {
        inorder(node->left);
        node->record->displayFeeRecord();
        cout << "-----------------------------\n";
        inorder(node->right);
    }
}
// Function to add a new fee record
void FeeManagement::Add(int id, string name, int totalFee, int paid, int securityFee, string date) {
    FeeRecord* rec = new FeeRecord(id, name, totalFee, paid, securityFee, date);
    root = insert(root, rec);
    cout << "Record added successfully.\n";
}

void FeeManagement::Delete(int id) {
    root = remove(root, id);
    cout << "Record deleted if existed.\n";
}

void FeeManagement::Update(int id, int totalFee) {
    FeeNode* node = search(root, id);
    if (node) {
        node->record->totalFee = totalFee;
        node->record->feeDue = ((totalFee - node->record->feePaid) > 0) ? "Due" : "Cleared";
        cout << "Total fee updated.\n";
    } else {
        cout << "Record not found.\n";
    }
}

void FeeManagement::Search(int id) {
    FeeNode* node = search(root, id);
    if (node)
        node->record->displayFeeRecord();
    else
        cout << "Record not found.\n";
}

void FeeManagement::checkDue(int studentID) {
    FeeNode* node = search(root, studentID);
    if (node)
        cout << "Fee Due Status: " << node->record->feeDue << endl;
    else
        cout << "Student not found.\n";
}

void FeeManagement::displayAllFeeRecords() {
    if (root == nullptr)
        cout << "No records found.\n";
    else
        inorder(root);
}
