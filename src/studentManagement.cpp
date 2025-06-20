#include "StudentManagement.h"
#include "Animation.h"
#include <fstream>
#include <chrono>
#include <thread>
#include <iomanip>
#include <cstdlib>  // system("cls")

using json = nlohmann::json;

// Add new student
void StudentManagement::addStudent(Student* student) {
    if (students.find(student->studentId) != students.end()) {
        cout << "Student already exists!" << endl;
        return;
    }
    students[student->studentId] = student;
    Animation::typeEffect("Student added successfully!\n", 30);
   this_thread::sleep_for(chrono::milliseconds(500));
    system("cls");
}

// Delete student
void StudentManagement::deleteStudent(int studentId) {
    auto it = students.find(studentId);
    if (it != students.end()) {
        delete it->second;
        students.erase(it);
        Animation::typeEffect("Student deleted successfully!\n", 30);
        this_thread::sleep_for(chrono::milliseconds(500));
        system("cls");
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
        cout << "----------------------------------------------------" << endl;
        cout << "Student ID:  |" << student->studentId << endl;
        cout << "Student Name:|" << student->studentName << endl;
        cout << "CNIC:        |" << student->CNIC << endl;
        cout << "Address:     | " << student->studentAddress << endl;
        cout << "Phone:       | " << student->studentPhone << endl;
        cout << "----------------------------------------------------" << endl;
        
    }
}

// Check if student exists
bool StudentManagement::exists(int studentId) const {
    return students.find(studentId) != students.end();
}

// Save all students to JSON file
void StudentManagement::saveStudentsToFile(const string& filename) {
    json jArray = json::array();
    for (const auto& pair : students) {
        jArray.push_back(pair.second->toJson());
    }

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << setw(4) << jArray;
        outFile.close();
        cout << "Students saved to " << filename << endl;
    } else {
        cout << "Failed to save student data!" << endl;
    }
}

// Load all students from JSON file
void StudentManagement::loadStudentsFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "No student file found!" << endl;
        return;
    }

    json jArray;
    inFile >> jArray;
    inFile.close();

    for (const auto& j : jArray) {
        Student* student = new Student();
        student->fromJson(j);
        students[student->studentId] = student;
    }

    cout << "Students loaded from " << filename << endl;
}

// Update a specific student inside the file
void StudentManagement::updateStudentInFile(const string& filename, int studentId, const Student& updatedStudent) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << " Could not open file for updating!" << endl;
        return;
    }

    json jArray;
    inFile >> jArray;
    inFile.close();

    bool found = false;
    for (auto& j : jArray) {
        if (j["studentId"] == studentId) {
            j = updatedStudent.toJson();
            found = true;
            break;
        }
    }

    if (found) {
        ofstream outFile(filename);
        outFile << jArray.dump(4);
        outFile.close();
        cout << "Student updated in file successfully!" << endl;
    } else {
        cout << "Student ID not found in file." << endl;
    }
}
// Delete student from file
void StudentManagement::deleteStudentFromFile(const string& filename, int studentId) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Could not open file for deletion!" << endl;
        return;
    }

    json jArray;
    inFile >> jArray;
    inFile.close();

    bool deleted = false;
    for (auto it = jArray.begin(); it != jArray.end(); ++it) {
        if ((*it)["studentId"] == studentId) {
            jArray.erase(it);
            deleted = true;
            break;
        }
    }

    if (deleted) {
        ofstream outFile(filename);
        outFile << jArray.dump(4);
        outFile.close();
        cout << " Student deleted from file successfully!" << endl;
    } else {
        cout << " Student ID not found in file." << endl;
    }
}
