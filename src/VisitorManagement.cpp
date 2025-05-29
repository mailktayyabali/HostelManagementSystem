#include <iostream>
#include <string>
using namespace std;

class VisitorNode {
   
public:
       int visitorId;
    string visitorName;
    string purpose;
    int date;
    string visitTo;
    string timeIn;
    string timeOut;
    VisitorNode* next;

    VisitorNode(int id, string name, string purp, int d, string to, string inTime, string outTime) {
        visitorId = id;
        visitorName = name;
        purpose = purp;
        date = d;
        visitTo = to;
        timeIn = inTime;
        timeOut = outTime;
        next = nullptr;
    }
};

class VisitorManagement {
private:
    VisitorNode* head;

public:
    VisitorManagement() {
        head = nullptr;
    }

    void Add(int id, string name, string purp, int d, string to, string inTime, string outTime) {
        VisitorNode* newNode = new VisitorNode(id, name, purp, d, to, inTime, outTime);
        if (head == nullptr) {
            head = newNode;
            return;
        }
        VisitorNode* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    void View() {
        VisitorNode* temp = head;
        if (temp == nullptr) {
            cout << "No visitor records found.\n";
            return;
        }

        cout << "Visitor Records:\n";
        while (temp != nullptr) {
            cout << "Visitor ID: " << temp->visitorId << endl;
            cout << "Name: " << temp->visitorName << endl;
            cout << "Purpose: " << temp->purpose << endl;
            cout << "Date: " << temp->date << endl;
            cout << "Visiting: " << temp->visitTo << endl;
            cout << "Time In: " << temp->timeIn << endl;
            cout << "Time Out: " << temp->timeOut << endl;
            cout << "-------------------------\n";
            temp = temp->next;
        }
    }

    void Search(int id) {
    VisitorNode* temp = head;
    while (temp != nullptr) {
        if (temp->visitorId == id) {
            cout << "Visitor Found:\n";
            cout << "Visitor ID: " << temp->visitorId << endl;
            cout << "Name: " << temp->visitorName << endl;
            cout << "Purpose: " << temp->purpose << endl;
            cout << "Date: " << temp->date << endl;
            cout << "Visiting: " << temp->visitTo << endl;
            cout << "Time In: " << temp->timeIn << endl;
            cout << "Time Out: " << temp->timeOut << endl;
            return;
        }
        temp = temp->next;
    }
    cout << "No visitor found with ID " << id << ".\n";
}
    void DeleteLast() {
        if (head == nullptr) {
            cout << "No records found to delete!\n";
            return;
        }

        if (head->next == nullptr) {
            delete head;
            head = nullptr;
            cout << "Record deleted successfully!\n";
            return;
        }

        VisitorNode* prev = nullptr;
        VisitorNode* temp = head;

        while (temp->next != nullptr) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = nullptr;
        delete temp;
        cout << "Last record deleted successfully!\n";
    }

    void Update(int id) {
    VisitorNode* temp = head;
    while (temp != nullptr) {
        if (temp->visitorId == id) {
            cout << "Enter new name: ";
            cin.ignore(); 
            getline(cin, temp->visitorName);

            cout << "Enter new purpose: ";
            getline(cin, temp->purpose);

            cout << "Enter new date (as integer): ";
            cin >> temp->date;
            cin.ignore();

            cout << "Enter new visiting to: ";
            getline(cin, temp->visitTo);

            cout << "Enter new time in: ";
            getline(cin, temp->timeIn);

            cout << "Enter new time out: ";
            getline(cin, temp->timeOut);

            cout << "Record updated successfully!\n";
            return;
        }
        temp = temp->next;
    }
    cout << "No record found with ID " << id << ".\n";
}
};


