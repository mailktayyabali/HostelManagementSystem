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

            if (prev == nullptr) {
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

void MessAttendanceManagement::DeleteByDateAndMeal(int studentId, const string& date, const string& mealType) {
    if (front == nullptr) {
        cout << "No attendance records to delete.\n";
        return;
    }

    AttendanceNode* current = front;
    AttendanceNode* prev = nullptr;
    bool deleted = false;

    while (current != nullptr) {
        if (current->studentId == studentId && current->date == date && current->mealType == mealType) {
            if (current == front) {
                front = front->next;
                if (current == rear) rear = nullptr;
                delete current;
            } else {
                prev->next = current->next;
                if (current == rear) rear = prev;
                delete current;
            }
            deleted = true;
            cout << "Attendance deleted for Student ID " << studentId
                 << " on " << date << " for " << mealType << ".\n";
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!deleted) {
        cout << "No matching attendance found for deletion.\n";
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

void MessAttendanceManagement::saveToFile(const string& path) {
    json jArray = json::array();
    AttendanceNode* current = front;
    while (current != nullptr) {
        jArray.push_back(current->toJson());
        current = current->next;
    }

    ofstream out(path);
    if (out.is_open()) {
        out << jArray.dump(4);
        out.close();
        cout << "Attendance saved to file: " << path << endl;
    } else {
        cout << "Failed to save attendance to file.\n";
    }
}

void MessAttendanceManagement::loadFromFile(const string& path) {
    ifstream in(path);
    if (!in.is_open()) {
        cout << "Attendance file not found.\n";
        return;
    }

    json jArray;
    in >> jArray;
    in.close();

    while (front != nullptr) Dequeue();

    for (const auto& j : jArray) {
        AttendanceNode* node = AttendanceNode::fromJson(j);
        if (rear == nullptr) {
            front = rear = node;
        } else {
            rear->next = node;
            rear = node;
        }
    }

    cout << "Attendance loaded from file: " << path << endl;
}
void MessAttendanceManagement::deleteFromFile(const string& path, int studentId) {
    ifstream in(path);
    if (!in.is_open()) {
        cout << "⚠ Could not open file: " << path << endl;
        return;
    }

    json jArray;
    in >> jArray;
    in.close();

    bool found = false;
    json updatedArray = json::array();

    for (const auto& entry : jArray) {
        if (entry["studentId"] != studentId) {
            updatedArray.push_back(entry);
        } else {
            found = true;
        }
    }

    if (!found) {
        cout << "No records found for Student ID " << studentId << " in file.\n";
        return;
    }

    ofstream out(path);
    if (out.is_open()) {
        out << updatedArray.dump(4);
        out.close();
        cout << "Records for Student ID " << studentId << " deleted from file.\n";
    } else {
        cout << "Failed to write updated records to file.\n";
    }
}
void MessAttendanceManagement::deleteFromFile(const string& path, int studentId, const string& date, const string& mealType) {
    ifstream in(path);
    if (!in.is_open()) {
        cout << " Could not open file: " << path << endl;
        return;
    }

    json jArray;
    in >> jArray;
    in.close();

    bool deleted = false;
    json updatedArray = json::array();

    for (const auto& entry : jArray) {
        if (entry["studentId"] == studentId &&
            entry["date"] == date &&
            entry["mealType"] == mealType) {
            deleted = true;
        } else {
            updatedArray.push_back(entry);
        }
    }

    if (!deleted) {
        cout << " No matching record found for deletion in file.\n";
        return;
    }

    ofstream out(path);
    if (out.is_open()) {
        out << updatedArray.dump(4);
        out.close();
        cout << " Record deleted for Student ID " << studentId << " on " << date << " (" << mealType << ").\n";
    } else {
        cout << " Failed to write updated records to file.\n";
    }
}
