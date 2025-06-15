#ifndef VISITOR_MANAGEMENT_H
#define VISITOR_MANAGEMENT_H

#include <string>
using namespace std;

class StudentManagement; // Forward declaration

class VisitorManagement {
private:
    struct VisitorNode {
        int visitorID;
        int studentID;
        string visitorName;
        string purpose;
        string visitDate;
        VisitorNode* next;
    };

    VisitorNode* head;
    int nextVisitorID;              // Auto-incrementing ID
    StudentManagement* sm;         // Pointer to StudentManagement for ID verification

public:
    VisitorManagement(StudentManagement* sm);
    ~VisitorManagement();

    void Add(int studentID, const string& name, const string& purpose, const string& date);
    void Delete(int visitorID); // Delete by visitorID now
    void Update(int visitorID, const string& newName, const string& newPurpose, const string& newDate);
    void Search(int visitorID);
    void View();
};

#endif
