#include "MessAttendanceManagement.h"

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
