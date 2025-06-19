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
        cout << "Cannot add attendance. Student ID " << studentId << " is not registered.\n";
        return;
    }

    // Check if the student already has the same meal on the same date
    AttendanceNode* temp = front;
    while (temp != nullptr) {
        if (temp->studentId == studentId && temp->date == date && temp->mealType == mealType) {
            cout << "Student ID " << studentId << " has already taken " << mealType << " on " << date << ".\n";
            return;
        }
        temp = temp->next;
    }

    AttendanceNode* newNode = new AttendanceNode(studentId, date, mealType);

    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }

    cout << "Attendance added for Student ID " << studentId
         << " on " << date << " for " << mealType << ".\n";
}

void MessAttendanceManagement::Dequeue() {
    if (front == nullptr) {
        cout << "No attendance records to remove.\n";
        return;
    }

    AttendanceNode* temp = front;
    front = front->next;

    if (front == nullptr) rear = nullptr;

    cout << "Removed attendance for Student ID " << temp->studentId
         << " on " << temp->date << " (" << temp->mealType << ").\n";

    delete temp;
}

void MessAttendanceManagement::DeleteByStudentId(int studentId) {
    if (front == nullptr) {
        cout << "No attendance records.\n";
        return;
    }

    AttendanceNode* curr = front;
    AttendanceNode* prev = nullptr;
    bool found = false;

    while (curr != nullptr) {
        if (curr->studentId == studentId) {
            found = true;
            AttendanceNode* toDelete = curr;

            if (prev == nullptr) { // deleting front
                front = curr->next;
                if (rear == curr) rear = nullptr;
                curr = front;
            } else {
                prev->next = curr->next;
                if (rear == curr) rear = prev;
                curr = curr->next;
            }

            delete toDelete;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    if (found) {
        cout << "All records for Student ID " << studentId << " deleted.\n";
    } else {
        cout << "No records found for Student ID " << studentId << ".\n";
    }
}

void MessAttendanceManagement::Search(int studentId) {
    AttendanceNode* temp = front;
    bool found = false;

    while (temp != nullptr) {
        if (temp->studentId == studentId) {
            if (!found) {
                cout << "\nAttendance for Student ID " << studentId << ":\n";
                cout << "----------------------------------------\n";
            }
            cout << "Date: " << temp->date << " | Meal: " << temp->mealType << "\n";
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "No attendance found for Student ID " << studentId << ".\n";
    }
}

void MessAttendanceManagement::ViewAll() {
    if (front == nullptr) {
        cout << "No attendance records found.\n";
        return;
    }

    AttendanceNode* temp = front;
    cout << "\nMess Attendance Records:\n";
    cout << "----------------------------------------\n";
    while (temp != nullptr) {
        cout << "Student ID: " << temp->studentId
             << " | Date: " << temp->date
             << " | Meal: " << temp->mealType << endl;
        temp = temp->next;
    }
}
