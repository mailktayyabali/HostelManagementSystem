#ifndef VISITORMANAGEMENT_H
#define VISITORMANAGEMENT_H

#include <string>
using namespace std;

class VisitorManagement {
private:
    struct Visitor {
        int visitorID;
        string name;
        string purpose;
        string visitDate;
        Visitor* next;
    };

    Visitor* head;

public:
    VisitorManagement();                  
    ~VisitorManagement();                 

    void Add(int id, const string& name, const string& purpose, const string& date);
    bool Delete(int id);
    bool Update(int id, const string& name, const string& purpose, const string& date);
    bool Search(int id);
    void View();
};

#endif
