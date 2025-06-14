#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#include <iostream>
#include <string>
#include <unordered_map>
#include "../Database/json.hpp" // Adjust the path if needed

using namespace std;
using json = nlohmann::json;

class Student {
public:
    int studentId;
    string studentName;
    string CNIC;
    string studentAddress;
    string studentPhone;

    json toJson() const {
        return {
            {"studentId", studentId},
            {"studentName", studentName},
            {"CNIC", CNIC},
            {"studentAddress", studentAddress},
            {"studentPhone", studentPhone}
        };
    }

    void fromJson(const json& j) {
        studentId = j.at("studentId").get<int>();
        studentName = j.at("studentName").get<string>();
        CNIC = j.at("CNIC").get<string>();
        studentAddress = j.at("studentAddress").get<string>();
        studentPhone = j.at("studentPhone").get<string>();
    }
};

class StudentManagement {
public:
    void addStudent(Student* student);
    void deleteStudent(int studentId);
    void updateStudent(int studentId, Student* updatedStudent);
    void viewStudents();
    bool exists(int studentId) const;

    // File handling
    void saveStudentsToFile(const string& filename);
    void loadStudentsFromFile(const string& filename);
    void updateStudentInFile(const string& filename, int studentId, const Student& updatedStudent);
    void deleteStudentFromFile(const string& filename, int studentId);

private:
    unordered_map<int, Student*> students;
};


#endif
