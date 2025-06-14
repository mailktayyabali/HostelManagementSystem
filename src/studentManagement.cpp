#include "StudentManagement.h"
#include <windows.h>   // for Sleep
#include <cstdlib>    // for system("cls")

// Validate CNIC format
bool isValidCNIC(const string& cnic) {
    for (char c : cnic) {
        if (!isdigit(c) && c != '-') {
            return false;
        }
    }
    return !cnic.empty();
}

// Add new student
void StudentManagement::addStudent(Student* student) {
    if (students.find(student->studentId) != students.end()) {
        cout << "Student already exists!" << endl;
        return;
    }
    students[student->studentId] = student;
    cout << "Student added successfully!" << endl;
    Sleep(1000); // Sleep for 1 second (Windows)
    system("cls"); // For Linux use: system("clear");
}

// Delete student
void StudentManagement::deleteStudent(int studentId) {
    auto it = students.find(studentId);
    if (it != students.end()) {
        delete it->second;
        students.erase(it);
        cout << "Student deleted successfully!" << endl;
    } else {
        cout << "Student not found!" << endl;
    }
}

// Update student details
void StudentManagement::updateStudent(int studentId, Student* updatedStudent) {
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

// Display all students
void StudentManagement::viewStudents() {
    if (students.empty()) {
        cout << "No student records found!" << endl;
        return;
    }

    for (const auto& pair : students) {
        const Student* student = pair.second;
        cout << "Student ID: " << student->studentId << endl;
        cout << "Student Name: " << student->studentName << endl;
        cout << "CNIC: " << student->CNIC << endl;
        cout << "Address: " << student->studentAddress << endl;
        cout << "Phone: " << student->studentPhone << endl;
        cout << "--------------------------" << endl;
    }
}

// Check if student exists
bool StudentManagement::exists(int studentId) const {
    return students.find(studentId) != students.end();
}

// Get pointer to student by ID
Student* StudentManagement::getStudent(int studentId) const {
    auto it = students.find(studentId);
    if (it != students.end()) {
        return it->second;
    }
    return nullptr;
}
