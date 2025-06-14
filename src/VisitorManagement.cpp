#include "VisitorManagement.h"
#include <iostream>
using namespace std;

VisitorManagement::VisitorManagement(StudentManagement* sm) {
    head = nullptr;
    studentManager = sm;
}

VisitorManagement::~VisitorManagement() {
    Visitor* temp;
    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }
}

void VisitorManagement::Add(int visitorID, const string& name, const string& address,
                            const string& cnic, const string& contactNumber,
                            int studentID, const string& visitDate) {
    if (!studentManager->exists(studentID)) {
        cout << "Error: Student with ID " << studentID << " does not exist.\n";
        return;
    }

    Student* student = studentManager->getStudent(studentID);
string studentName = student ? student->studentName : "Unknown";

    Visitor* newVisitor = new Visitor{visitorID, name, address, cnic, contactNumber,
                                      visitDate, studentID, studentName, head};
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

bool VisitorManagement::Update(int visitorID, const string& name, const string& address,
                               const string& cnic, const string& contactNumber,
                               int studentID, const string& visitDate) {
    Visitor* current = head;
    while (current != nullptr) {
        if (current->visitorID == visitorID) {
            if (!studentManager->exists(studentID)) {
                cout << "Error: Student with ID " << studentID << " does not exist.\n";
                return false;
            }

            Student* student = studentManager->getStudent(studentID);
string studentName = student ? student->studentName : "Unknown";

            current->name = name;
            current->address = address;
            current->cnic = cnic;
            current->contactNumber = contactNumber;
            current->studentID = studentID;
            current->studentName = studentName;
            current->visitDate = visitDate;
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
                 << "\nAddress: " << current->address
                 << "\nCNIC: " << current->cnic
                 << "\nContact Number: " << current->contactNumber
                 << "\nVisit Date: " << current->visitDate
                 << "\nStudent Name: " << current->studentName
                 << "\nStudent ID: " << current->studentID << "\n";
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
             << "\nAddress: " << current->address
             << "\nCNIC: " << current->cnic
             << "\nContact Number: " << current->contactNumber
             << "\nVisit Date: " << current->visitDate
             << "\nStudent Name: " << current->studentName
             << "\nStudent ID: " << current->studentID
             << "\n--------------------------";
        current = current->next;
    }
}
