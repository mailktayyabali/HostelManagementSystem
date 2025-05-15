#include <iostream>
#include <vector>
using namespace std;

class Student {
public:
    int studentId;
    string studentName;
    double CNIC;
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
    vector<Student*> students; // Vector for fully dynamic memory
};

void studentManagement::addStudent(Student* student) {
    students.push_back(student);
    cout << "Student added successfully!" << endl;
}

void studentManagement::deleteStudent(int studentId) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if ((*it)->studentId == studentId) {
            delete *it;
            students.erase(it);
            cout << "Student deleted successfully!" << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}

void studentManagement::updateStudent(int studentId, Student* updatedStudent) {
    for (auto& student : students) {
        if (student->studentId == studentId) {
            // Only copy the fields that should be updated
            student->studentName = updatedStudent->studentName;
            student->CNIC = updatedStudent->CNIC;
            student->studentAddress = updatedStudent->studentAddress;
            student->studentPhone = updatedStudent->studentPhone;

            cout << "Student updated successfully!" << endl;
            return;
        }
    }
    cout << "Student not found!" << endl;
}

void studentManagement::viewStudents() {
    for (const auto& student : students) {
        cout << "ID: " << student->studentId << endl;
        cout << "Name: " << student->studentName << endl;
        cout << "CNIC: " << student->CNIC << endl;
        cout << "Address: " << student->studentAddress << endl;
        cout << "Phone: " << student->studentPhone << endl;
        cout << "--------------------------" << endl;
    }
}

bool studentManagement::exists(int studentId) const {
    for (const auto& student : students) {
        if (student->studentId == studentId) return true;
    }
    return false;
}
