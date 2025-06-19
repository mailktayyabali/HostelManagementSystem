#ifndef MESSATTENDANCEMANAGEMENT_H
#define MESSATTENDANCEMANAGEMENT_H

#include <iostream>
#include <string>
#include <fstream>
#include "StudentManagement.h"
#include "../Database/json.hpp"
using namespace std;
using json = nlohmann::json;


struct AttendanceNode {
    int studentId;
    string date;
    string mealType;
    AttendanceNode* next;

    AttendanceNode(int id, string d, string m)
        : studentId(id), date(d), mealType(m), next(nullptr) {}

    json toJson() const {
        return json{
            {"studentId", studentId},
            {"date", date},
            {"mealType", mealType}
        };
    }

    static AttendanceNode* fromJson(const json& j) {
        return new AttendanceNode(j["studentId"], j["date"], j["mealType"]);
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
    void DeleteByStudentId(int studentId);
    void DeleteByDateAndMeal(int studentId, const string& date, const string& mealType);
    void Search(int studentId);
    void ViewAll();

    void saveToFile(const string& path);
    void loadFromFile(const string& path);
    void deleteFromFile(const string& path, int studentId);

};

#endif
