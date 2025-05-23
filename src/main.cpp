#include <iostream>
#include "StudentManagement.h"
#include "FeeManagement.h"
#include "MessAttendanceManagement.h"

using namespace std;

int main() {
    StudentManagement sm;
    FeeManagement fm;
    MessAttendanceManagement mam;
    int mainChoice;

    do {
        cout << "\n===== Hostel Management System =====\n";
        cout << "1. Student Management\n";
        cout << "2. Fee Management\n";
        cout << "3. Mess Attendance Management\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input! Try again.\n";
            continue;
        }

        switch (mainChoice) {
            case 1: {
                int choice;
                do {
                    cout << "\n--- Student Management Menu ---\n";
                    cout << "1. Add Student\n";
                    cout << "2. Delete Student\n";
                    cout << "3. Update Student\n";
                    cout << "4. View All Students\n";
                    cout << "5. Back to Main Menu\n";
                    cout << "Enter choice: ";
                    cin >> choice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Try again.\n";
                        continue;
                    }

                    switch (choice) {
                        case 1: {
                            Student* newStudent = new Student();
                            cout << "Enter ID: ";
                            cin >> newStudent->studentId;
                            cin.ignore();

                            cout << "Enter Name: ";
                            getline(cin, newStudent->studentName);

                            cout << "Enter CNIC (e.g., 12345-1234567-1): ";
                            getline(cin, newStudent->CNIC);
                            if (!isValidCNIC(newStudent->CNIC)) {
                                cout << "Invalid CNIC format!\n";
                                delete newStudent;
                                break;
                            }

                            cout << "Enter Address: ";
                            getline(cin, newStudent->studentAddress);

                            cout << "Enter Phone: ";
                            getline(cin, newStudent->studentPhone);

                            sm.addStudent(newStudent);
                            break;
                        }

                        case 2: {
                            int id;
                            cout << "Enter Student ID to delete: ";
                            cin >> id;
                            sm.deleteStudent(id);
                            break;
                        }

                        case 3: {
                            int id;
                            cout << "Enter Student ID to update: ";
                            cin >> id;
                            cin.ignore();

                            if (!sm.exists(id)) {
                                cout << "Student not found!\n";
                                break;
                            }

                            Student* updatedStudent = new Student();
                            updatedStudent->studentId = id;

                            cout << "Enter New Name: ";
                            getline(cin, updatedStudent->studentName);

                            cout << "Enter New CNIC: ";
                            getline(cin, updatedStudent->CNIC);
                            if (!isValidCNIC(updatedStudent->CNIC)) {
                                cout << "Invalid CNIC format!\n";
                                delete updatedStudent;
                                break;
                            }

                            cout << "Enter New Address: ";
                            getline(cin, updatedStudent->studentAddress);

                            cout << "Enter New Phone: ";
                            getline(cin, updatedStudent->studentPhone);

                            sm.updateStudent(id, updatedStudent);
                            delete updatedStudent;
                            break;
                        }

                        case 4:
                            sm.viewStudents();
                            break;

                        case 5:
                            cout << "Returning to main menu...\n";
                            break;

                        default:
                            cout << "Invalid option! Please try again.\n";
                    }

                } while (choice != 5);
                break;
            }

            case 2: {
                int choice;
                do {
                    cout << "\n-- Fee Management Menu --" << endl;
                    cout << "1. Add Fee Record" << endl;
                    cout << "2. Delete Fee Record" << endl;
                    cout << "3. Update Total Fee" << endl;
                    cout << "4. Search Fee Record" << endl;
                    cout << "5. View All Fee Records" << endl;
                    cout << "6. Check Fee Due" << endl;
                    cout << "7. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Try again.\n";
                        continue;
                    }

                    switch (choice) {
                        case 1: {
                            int id, total, paid, security;
                            string name, date;
                            cout << "Enter Student ID: "; cin >> id;
                            cin.ignore();
                            cout << "Enter Name: "; getline(cin, name);
                            cout << "Enter Total Fee: "; cin >> total;
                            cout << "Enter Fee Paid: "; cin >> paid;
                            cout << "Enter Security Fee: "; cin >> security;
                            cin.ignore();
                            cout << "Enter Payment Date: "; getline(cin, date);
                            fm.Add(id, name, total, paid, security, date);
                            break;
                        }
                        case 2: {
                            int id;
                            cout << "Enter Student ID to delete: ";
                            cin >> id;
                            fm.Delete(id);
                            break;
                        }
                        case 3: {
                            int id, total;
                            cout << "Enter Student ID to update total fee: ";
                            cin >> id;
                            cout << "Enter new Total Fee: ";
                            cin >> total;
                            fm.Update(id, total);
                            break;
                        }
                        case 4: {
                            int id;
                            cout << "Enter Student ID to search: ";
                            cin >> id;
                            fm.Search(id);
                            break;
                        }
                        case 5:
                            fm.displayAllFeeRecords();
                            break;
                        case 6: {
                            int id;
                            cout << "Enter Student ID to check due: ";
                            cin >> id;
                            fm.checkDue(id);
                            break;
                        }
                        case 7:
                            cout << "Returning to main menu...\n";
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                } while (choice != 7);
                break;
            }

            case 3: {
                int choice;
                do {
                    cout << "\n-- Mess Attendance Menu --" << endl;
                    cout << "1. Add Attendance" << endl;
                    cout << "2. Delete Attendance" << endl;
                    cout << "3. View All Attendance" << endl;
                    cout << "4. Search Attendance by Student ID" << endl;
                    cout << "5. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> choice;

                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid input! Try again.\n";
                        continue;
                    }

                    switch (choice) {
                        case 1: {
                            int studentId;
                            string date, meal;
                            cout << "Enter Student ID: ";
                            cin >> studentId;
                            cout << "Enter Date (YYYY-MM-DD): ";
                            cin >> date;
                            cout << "Enter Meal Type (breakfast/lunch/dinner): ";
                            cin >> meal;
                            mam.Enqueue(studentId, date, meal);
                            break;
                        }
                        case 2: {
                            int id;
                            cout << "Enter Student ID to delete attendance: ";
                            cin >> id;
                            mam.Dequeue(id);
                            break;
                        }
                        case 3:
                            mam.ViewAll();
                            break;

                        case 4: {
                            int id;
                            cout << "Enter Student ID to search attendance: ";
                            cin >> id;
                            mam.Search(id);
                            break;
                        }

                        case 5:
                            cout << "Returning to main menu...\n";
                            break;

                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                } while (choice != 5);
                break;
            }

            case 4:
                cout << "Exiting Program... Goodbye!\n";
                break;

            default:
                cout << "Invalid main menu choice. Try again.\n";
        }

    } while (mainChoice != 4);

    return 0;
}
