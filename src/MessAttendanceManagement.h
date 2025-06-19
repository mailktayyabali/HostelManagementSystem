#ifndef MESSATTENDANCEMANAGEMENT_H
#define MESSATTENDANCEMANAGEMENT_H

#include <iostream>
#include <string>
#include "StudentManagement.h"

using namespace std;

struct AttendanceNode {
    int studentId;
    string date;
    string mealType;
    AttendanceNode* next;

    AttendanceNode(int id, string d, string m)
        : studentId(id), date(d), mealType(m), next(nullptr) {}
};

class MessAttendanceManagement {
private:
    AttendanceNode* front;
    AttendanceNode* rear;
    StudentManagement* studentManager;

public:
    MessAttendanceManagement(StudentManagement* sm);
    ~MessAttendanceManagement();

    void Enqueue(int studentId, string date, string mealType);
    void Dequeue();
    void DeleteByStudentId(int studentId); 
    void Search(int studentId);
    void ViewAll();
};

#endif
