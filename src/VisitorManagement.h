#ifndef VISITORMANAGEMENT_H
#define VISITORMANAGEMENT_H

#include <string>
#include "StudentManagement.h"
using namespace std;

class VisitorManagement {
private:
    struct Visitor {
        int visitorID;
        string name;
        string address;
        string cnic;
        string contactNumber;
        string visitDate;
        int studentID;
        string studentName;
        Visitor* next;
    };

    Visitor* head;
    StudentManagement* studentManager;

public:
    VisitorManagement(StudentManagement* sm);  // Constructor with student manager link
    ~VisitorManagement();

    void Add(int visitorID, const string& name, const string& address,
             const string& cnic, const string& contactNumber,
             int studentID, const string& visitDate);

    bool Delete(int id);
    bool Update(int visitorID, const string& name, const string& address,
                const string& cnic, const string& contactNumber,
                int studentID, const string& visitDate);

    bool Search(int id);
    void View();
};

#endif
