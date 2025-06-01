#ifndef MESS_ATTENDANCE_MANAGEMENT_H
#define MESS_ATTENDANCE_MANAGEMENT_H

#include <iostream>
#include <string>
#include "StudentManagement.h"
using namespace std;

struct AttendanceNode {
    int studentId;
    string date;
    string mealType;
    AttendanceNode* next;

    AttendanceNode(int id, string d, string meal)
        : studentId(id), date(d), mealType(meal), next(nullptr) {}
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
    void ViewAll();
    void Search(int studentId);
};

#endif
