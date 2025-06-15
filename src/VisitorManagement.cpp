#include "VisitorManagement.h"
#include "StudentManagement.h" // For ID verification
#include "Validate.h"
#include <iostream>

using namespace std;

VisitorManagement::VisitorManagement(StudentManagement* sm) {
    this->sm = sm;
    head = nullptr;
    nextVisitorID = 1;  // Start from ID 1
}

VisitorManagement::~VisitorManagement() {
    VisitorNode* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void VisitorManagement::Add(int studentID, const string& name, const string& purpose, const string& date) {
    if (!sm->exists(studentID)) {
        cout << "Student ID not found! Cannot add visitor.\n";
        return;
    }

    VisitorNode* newNode = new VisitorNode{nextVisitorID++, studentID, name, purpose, date, nullptr};

    if (!head) {
        head = newNode;
    } else {
        VisitorNode* temp = head;
        while (temp->next) temp = temp->next;
        temp->next = newNode;
    }

    cout << "Visitor added successfully. Visitor ID: " << newNode->visitorID << "\n";
}

void VisitorManagement::Delete(int visitorID) {
    if (!head) {
        cout << "Visitor list is empty.\n";
        return;
    }

    VisitorNode* temp = head;
    VisitorNode* prev = nullptr;

    while (temp && temp->visitorID != visitorID) {
        prev = temp;
        temp = temp->next;
    }

    if (!temp) {
        cout << "Visitor not found.\n";
        return;
    }

    if (!prev) {
        head = temp->next;
    } else {
        prev->next = temp->next;
    }

    delete temp;
    cout << "Visitor deleted successfully.\n";
}

void VisitorManagement::Update(int visitorID, const string& newName, const string& newPurpose, const string& newDate) {
    VisitorNode* temp = head;
    while (temp) {
        if (temp->visitorID == visitorID) {
            temp->visitorName = newName;
            temp->purpose = newPurpose;
            temp->visitDate = newDate;
            cout << "Visitor record updated.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Visitor not found.\n";
}

void VisitorManagement::Search(int visitorID) {
    VisitorNode* temp = head;
    while (temp) {
        if (temp->visitorID == visitorID) {
            cout << "\nVisitor Info:\n";
            cout << "Visitor ID: " << temp->visitorID << "\n";
            cout << "Student ID: " << temp->studentID << "\n";
            cout << "Visitor Name: " << temp->visitorName << "\n";
            cout << "Purpose: " << temp->purpose << "\n";
            cout << "Visit Date: " << temp->visitDate << "\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Visitor not found.\n";
}

void VisitorManagement::View() {
    if (!head) {
        cout << "No visitor records.\n";
        return;
    }

    VisitorNode* temp = head;
    cout << "\nAll Visitors:\n";
    while (temp) {
        cout << "--------------------------\n";
        cout << "Visitor ID: " << temp->visitorID << "\n";
        cout << "Student ID: " << temp->studentID << "\n";
        cout << "Visitor Name: " << temp->visitorName << "\n";
        cout << "Purpose: " << temp->purpose << "\n";
        cout << "Visit Date: " << temp->visitDate << "\n";
        temp = temp->next;
    }
}
