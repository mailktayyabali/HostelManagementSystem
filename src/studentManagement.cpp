#include <iostream>
#include <vector>
#include<cstdlib>
#include <unordered_map>
#include <unistd.h>
using namespace std;

class Student {
public:
    int studentId;
    string studentName;
    string CNIC; // Changed from double to string
    string studentAddress;
    string studentPhone;
};

class studentManagement {
public:
    void addStudent(Student* student);
    void deleteStudent(int studentId);
    void updateStudent(int studentId, Student* updatedStudent);
    void viewStudents();
    bool exists(int studentId) const;

private:
    unordered_map<int, Student*> students; // Hash table for fast lookup by studentId
};

// Helper function to validate CNIC
bool isValidCNIC(const string& cnic) {
    for (char c : cnic) {
        if (!isdigit(c) && c != '-') {
            return false;
        }
    }
    return !cnic.empty();
}

void studentManagement::addStudent(Student* student) {
    if (students.find(student->studentId) != students.end()) {
        cout << "Student already exists!" << endl;
        return;
    }
    students[student->studentId] = student;
    cout << "Student added successfully!" << endl;
    sleep(2);
    system("cls");
}

void studentManagement::deleteStudent(int studentId) {
    auto it = students.find(studentId);
    if (it != students.end()) {
        delete it->second;
        students.erase(it);
        cout << "Student deleted successfully!" << endl;
    } else {
        cout << "Student not found!" << endl;
    }
}

void studentManagement::updateStudent(int studentId, Student* updatedStudent) {
    auto it = students.find(studentId);
    if (it != students.end()) {
        it->second->studentName = updatedStudent->studentName;
        it->second->CNIC = updatedStudent->CNIC;
        it->second->studentAddress = updatedStudent->studentAddress;
        it->second->studentPhone = updatedStudent->studentPhone;
        cout << "Student updated successfully!" << endl;
    } else {
        cout << "Student not found!" << endl;
    }
}

void studentManagement::viewStudents() {
    for (const auto& pair : students) {
        const Student* student = pair.second;
        cout << "ID: " << student->studentId << endl;
        cout << "Name: " << student->studentName << endl;
        cout << "CNIC: " << student->CNIC << endl;
        cout << "Address: " << student->studentAddress << endl;
        cout << "Phone: " << student->studentPhone << endl;
        cout << "--------------------------" << endl;
    }
}

bool studentManagement::exists(int studentId) const {
    return students.find(studentId) != students.end();
}
