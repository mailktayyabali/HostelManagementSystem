#ifndef STUDENT_MANAGEMENT_H
#define STUDENT_MANAGEMENT_H

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;


class Student {
public:
    int studentId;
    string studentName;
    string CNIC;
    string studentAddress;
    string studentPhone;
};

class StudentManagement {
public:
    void addStudent(Student* student);
    void deleteStudent(int studentId);
    void updateStudent(int studentId, Student* updatedStudent);
    void viewStudents();
    bool exists(int studentId) const;

private:
    unordered_map<int, Student*> students;
};

// CNIC validation function
bool isValidCNIC(const string& cnic);

#endif
