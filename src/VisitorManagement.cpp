// VisitorManagement.cpp
#include "VisitorManagement.h"
#include "StudentManagement.h"
#include <iostream>
#include <fstream>
using namespace std;

VisitorManagement::VisitorManagement(StudentManagement* sm) : head(nullptr), nextVisitorID(1), sm(sm) {}

VisitorManagement::~VisitorManagement() {
    while (head) {
        VisitorNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void VisitorManagement::Add(int studentID, const string& name, const string& purpose, const string& date) {
    VisitorNode* newNode = new VisitorNode{nextVisitorID++, studentID, name, purpose, date, head};
    head = newNode;
    cout << "Visitor added successfully!" << endl;
}

void VisitorManagement::Delete(int visitorID) {
    VisitorNode* temp = head;
    VisitorNode* prev = nullptr;

    while (temp) {
        if (temp->visitorID == visitorID) {
            if (prev) prev->next = temp->next;
            else head = temp->next;
            delete temp;
            cout << "Visitor deleted." << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Visitor not found!" << endl;
}

void VisitorManagement::Update(int visitorID, const string& newName, const string& newPurpose, const string& newDate) {
    VisitorNode* temp = head;
    while (temp) {
        if (temp->visitorID == visitorID) {
            temp->visitorName = newName;
            temp->purpose = newPurpose;
            temp->visitDate = newDate;
            cout << "Visitor updated." << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Visitor not found!" << endl;
}

void VisitorManagement::Search(int visitorID) {
    VisitorNode* temp = head;
    while (temp) {
        if (temp->visitorID == visitorID) {
            cout << "Visitor ID: " << temp->visitorID << endl;
            cout << "Student ID: " << temp->studentID << endl;
            cout << "Name: " << temp->visitorName << endl;
            cout << "Purpose: " << temp->purpose << endl;
            cout << "Date: " << temp->visitDate << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "Visitor not found!" << endl;
}

void VisitorManagement::View() {
    VisitorNode* temp = head;
    if (!temp) {
        cout << "No visitors recorded." << endl;
        return;
    }

    while (temp) {
        cout << "Visitor ID: " << temp->visitorID << ", Student ID: " << temp->studentID
             << ", Name: " << temp->visitorName << ", Purpose: " << temp->purpose
             << ", Date: " << temp->visitDate << endl;
        temp = temp->next;
    }
}
bool VisitorManagement::exists(int visitorId) {
    VisitorNode* temp = head;
    while (temp) {
        if (temp->visitorID == visitorId) return true;
        temp = temp->next;
    }
    return false;
}

void VisitorManagement::saveVisitorsToFile(const string& filename) {
    json jArray = json::array();
    VisitorNode* temp = head;
    while (temp) {
        jArray.push_back(temp->toJson());
        temp = temp->next;
    }
    ofstream outFile(filename);
    outFile << jArray.dump(4);
    outFile.close();
    cout << "Visitors saved to file." << endl;
}

void VisitorManagement::loadVisitorsFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) return;

    json jArray;
    inFile >> jArray;
    inFile.close();

    while (head) {
        VisitorNode* temp = head;
        head = head->next;
        delete temp;
    }
    head = nullptr;
    nextVisitorID = 1;

    for (const auto& j : jArray) {
        VisitorNode* node = new VisitorNode();
        node->fromJson(j);
        node->next = head;
        head = node;
        if (node->visitorID >= nextVisitorID)
            nextVisitorID = node->visitorID + 1;
    }
    cout << "Visitors loaded from file." << endl;
}

void VisitorManagement::updateVisitorInFile(const string& filename, int visitorID) {
    ifstream inFile(filename);
    if (!inFile.is_open()) return;

    json jArray;
    inFile >> jArray;
    inFile.close();

    for (auto& j : jArray) {
        if (j["visitorID"] == visitorID) {
            VisitorNode* temp = head;
            while (temp) {
                if (temp->visitorID == visitorID) {
                    j = temp->toJson();
                    break;
                }
                temp = temp->next;
            }
            break;
        }
    }

    ofstream outFile(filename);
    outFile << jArray.dump(4);
    outFile.close();
    cout << "Visitor updated in file." << endl;
}

void VisitorManagement::deleteVisitorFromFile(const string& filename, int visitorID) {
    ifstream inFile(filename);
    if (!inFile.is_open()) return;

    json jArray;
    inFile >> jArray;
    inFile.close();

    json updatedArray = json::array();
    for (const auto& j : jArray) {
        if (j["visitorID"] != visitorID)
            updatedArray.push_back(j);
    }

    ofstream outFile(filename);
    outFile << updatedArray.dump(4);
    outFile.close();
    cout << "Visitor deleted from file." << endl;
}
