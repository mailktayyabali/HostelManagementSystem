#ifndef MESS_ATTENDANCE_MANAGEMENT_H
#define MESS_ATTENDANCE_MANAGEMENT_H

#include <iostream>
#include <string>
#include "../Database/json.hpp"
#include "StudentManagement.h"

using namespace std;
using json = nlohmann::json;

struct AttendanceNode {
    int studentId;
    string date;
    string mealType;
    AttendanceNode* next;

    AttendanceNode(int id, string d, string meal)
        : studentId(id), date(d), mealType(meal), next(nullptr) {}

    json toJson() const {
        return json{
            {"studentId", studentId},
            {"date", date},
            {"mealType", mealType}
        };
    }

    void fromJson(const json& j) {
        studentId = j.at("studentId").get<int>();
        date = j.at("date").get<string>();
        mealType = j.at("mealType").get<string>();
    }
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

    // JSON File Handling
    void saveAttendanceToFile(const string& filename);
    void loadAttendanceFromFile(const string& filename);
    void deleteAttendanceFromFile(const string& filename, int studentId, const string& date);
};

#endif
