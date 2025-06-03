#include "VisitorManagement.h"
#include <iostream>
using namespace std;

VisitorManagement::VisitorManagement() {
    head = nullptr;
}

VisitorManagement::~VisitorManagement() {
    Visitor* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void VisitorManagement::Add(int id, const string& name, const string& purpose, const string& date) {
    Visitor* newVisitor = new Visitor{ id, name, purpose, date, head };
    head = newVisitor;
    cout << "Visitor added successfully.\n";
}

bool VisitorManagement::Delete(int id) {
    Visitor* current = head;
    Visitor* prev = nullptr;

    while (current != nullptr) {
        if (current->visitorID == id) {
            if (prev == nullptr) head = current->next;
            else prev->next = current->next;
            delete current;
            cout << "Visitor deleted.\n";
            return true;
        }
        prev = current;
        current = current->next;
    }
    cout << "Visitor not found.\n";
    return false;
}

bool VisitorManagement::Update(int id, const string& name, const string& purpose, const string& date) {
    Visitor* current = head;
    while (current != nullptr) {
        if (current->visitorID == id) {
            current->name = name;
            current->purpose = purpose;
            current->visitDate = date;
            cout << "Visitor updated.\n";
            return true;
        }
        current = current->next;
    }
    cout << "Visitor not found.\n";
    return false;
}

bool VisitorManagement::Search(int id) {
    Visitor* current = head;
    while (current != nullptr) {
        if (current->visitorID == id) {
            cout << "Visitor Found:\n";
            cout << "ID: " << current->visitorID
                 << "\nName: " << current->name
                 << "\nPurpose: " << current->purpose
                 << "\nDate: " << current->visitDate << "\n";
            return true;
        }
        current = current->next;
    }
    cout << "Visitor not found.\n";
    return false;
}

void VisitorManagement::View() {
    if (head == nullptr) {
        cout << "No visitors recorded.\n";
        return;
    }

    Visitor* current = head;
    while (current != nullptr) {
        cout << "\nVisitor ID: " << current->visitorID
             << "\nName: " << current->name
             << "\nPurpose: " << current->purpose
             << "\nVisit Date: " << current->visitDate << "\n";
        current = current->next;
    }
}
