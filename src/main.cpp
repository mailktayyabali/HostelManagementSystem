#include "studentManagement.cpp"

int main() {
    studentManagement sm;
    int choice;

    do {
        cout << "\nStudent Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Update Student" << endl;
        cout << "4. View Students" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                Student* newStudent = new Student;
                cout << "Enter Student ID: ";
                cin >> newStudent->studentId;
                cout << "Enter Student Name: ";
                cin.ignore();
                getline(cin, newStudent->studentName);
                cout << "Enter CNIC: ";
                cin >> newStudent->CNIC;
                cout << "Enter Address: ";
                cin.ignore();
                getline(cin, newStudent->studentAddress);
                cout << "Enter Phone: ";
                cin >> newStudent->studentPhone;
                sm.addStudent(newStudent);
                break;
            }
            case 2: {
                int studentId;
                cout << "Enter Student ID to delete: ";
                cin >> studentId;
                sm.deleteStudent(studentId);
                break;
            }
            case 3: {
                int studentId;
                cout << "Enter Student ID to update: ";
                cin >> studentId;
                Student* updatedStudent = new Student;
                cout << "Enter Updated Student Name: ";
                cin.ignore();
                getline(cin, updatedStudent->studentName);
                cout << "Enter Updated CNIC: ";
                cin >> updatedStudent->CNIC;
                cout << "Enter Updated Address: ";
                cin.ignore();
                getline(cin, updatedStudent->studentAddress);
                cout << "Enter Updated Phone: ";
                cin >> updatedStudent->studentPhone;
                sm.updateStudent(studentId, updatedStudent);
                delete updatedStudent;
                break;
            }
            case 4:
                sm.viewStudents();
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 5);

    return 0;
}