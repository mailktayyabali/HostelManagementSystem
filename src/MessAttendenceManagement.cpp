#include "MessAttendanceManagement.h"
#include <fstream>
#include <iomanip>

MessAttendanceManagement::MessAttendanceManagement(StudentManagement* sm) {
    front = rear = nullptr;
    studentManager = sm;
}

MessAttendanceManagement::~MessAttendanceManagement() {
    while (front != nullptr) {
        Dequeue();
    }
}

void MessAttendanceManagement::Enqueue(int studentId, string date, string mealType) {
    if (!studentManager->exists(studentId)) {
        cout << "❌ Cannot add attendance. Student ID " << studentId << " is not registered.\n";
        return;
    }

    AttendanceNode* newNode = new AttendanceNode(studentId, date, mealType);

    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    cout << "✅ Attendance added for Student ID " << studentId
         << " on " << date << " for " << mealType << ".\n";
}

void MessAttendanceManagement::Dequeue() {
    if (front == nullptr) {
        cout << "⚠ No attendance records to remove.\n";
        return;
    }

    AttendanceNode* temp = front;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    cout << "🗑 Removed attendance for Student ID " << temp->studentId
         << " on " << temp->date << " (" << temp->mealType << ").\n";

    delete temp;
}

void MessAttendanceManagement::ViewAll() {
    if (front == nullptr) {
        cout << "⚠ No attendance records found.\n";
        return;
    }

    AttendanceNode* temp = front;
    cout << "\n📋 Mess Attendance Records:\n";
    cout << "----------------------------------------\n";
    while (temp != nullptr) {
        cout << "Student ID: " << temp->studentId
             << " | Date: " << temp->date
             << " | Meal: " << temp->mealType << endl;
        temp = temp->next;
    }
}

void MessAttendanceManagement::Search(int studentId) {
    bool found = false;
    AttendanceNode* temp = front;

    while (temp != nullptr) {
        if (temp->studentId == studentId) {
            if (!found) {
                cout << "\n🔍 Attendance for Student ID " << studentId << ":\n";
                cout << "----------------------------------------\n";
            }
            cout << "Date: " << temp->date << " | Meal: " << temp->mealType << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "❌ No attendance found for Student ID " << studentId << ".\n";
    }
}

// ✅ File Handling Implementation

void MessAttendanceManagement::saveAttendanceToFile(const string& filename) {
    json jArray = json::array();

    AttendanceNode* current = front;
    while (current != nullptr) {
        jArray.push_back(current->toJson());
        current = current->next;
    }

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << setw(4) << jArray;
        outFile.close();
        cout << "💾 Attendance saved to " << filename << endl;
    } else {
        cout << "❌ Failed to save attendance to file.\n";
    }
}

void MessAttendanceManagement::loadAttendanceFromFile(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "❌ Unable to open file: " << filename << endl;
        return;
    }

    json jArray;
    inFile >> jArray;
    inFile.close();

    front = rear = nullptr;

    for (const auto& j : jArray) {
        AttendanceNode* newNode = new AttendanceNode(0, "", "");
        newNode->fromJson(j);

        if (rear == nullptr) {
            front = rear = newNode;
        } else {
            rear->next = newNode;
            rear = newNode;
        }
    }

    cout << "📂 Attendance loaded from " << filename << endl;
}

void MessAttendanceManagement::deleteAttendanceFromFile(const string& filename, int studentId, const string& date) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "❌ Unable to open file: " << filename << endl;
        return;
    }

    json jArray;
    inFile >> jArray;
    inFile.close();

    json updatedArray = json::array();
    for (const auto& j : jArray) {
        if (j["studentId"] != studentId || j["date"] != date) {
            updatedArray.push_back(j);
        }
    }

    ofstream outFile(filename);
    if (outFile.is_open()) {
        outFile << setw(4) << updatedArray;
        outFile.close();
        cout << "🧹 Deleted attendance for Student ID " << studentId << " on " << date << " from file.\n";
    } else {
        cout << "❌ Failed to write to file during delete.\n";
    }
}
