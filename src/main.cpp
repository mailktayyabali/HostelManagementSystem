#include <iostream>
#include "StudentManagement.h"
#include "FeeManagement.h"
#include "MessAttendanceManagement.h"
#include "Room.h"
#include "Validate.h"

using namespace std;

int main() {
    StudentManagement sm;
    FeeManagement fm;
    MessAttendanceManagement mam;
    RoomManagement room(sm);
    int mainChoice;

    do {
        cout << "\n===== Hostel Management System =====\n";
        cout << "1. Student Management\n";
        cout << "2. Fee Management\n";
        cout << "3. Mess Attendance Management\n";
        cout << "4. Room Management\n";
        cout << "5. Exit\n";
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
                            newStudent->studentId = getValidatedInt("Enter ID: ");
                            newStudent->studentName = getValidatedString("Enter Name: ");
                            newStudent->CNIC = getValidatedCNIC("Enter CNIC (e.g., 12345-1234567-1): ");
                            newStudent->studentAddress = getValidatedString("Enter Address: ");
                            newStudent->studentPhone = getValidatedPhone("Enter Phone: ");
                            sm.addStudent(newStudent);
                            break;
                        }
                        case 2: {
                            int id = getValidatedInt("Enter Student ID to delete: ");
                            sm.deleteStudent(id);
                            break;
                        }
                        case 3: {
                            int id = getValidatedInt("Enter Student ID to update: ");
                            if (!sm.exists(id)) {
                                cout << "Student not found!\n";
                                break;
                            }
                            Student* updatedStudent = new Student();
                            updatedStudent->studentId = id;
                            updatedStudent->studentName = getValidatedString("Enter New Name: ");
                            updatedStudent->CNIC = getValidatedCNIC("Enter New CNIC: ");
                            updatedStudent->studentAddress = getValidatedString("Enter New Address: ");
                            updatedStudent->studentPhone = getValidatedPhone("Enter New Phone: ");
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
                    cout << "\n-- Fee Management Menu --\n";
                    cout << "1. Add Fee Record\n";
                    cout << "2. Delete Fee Record\n";
                    cout << "3. Update Total Fee\n";
                    cout << "4. Search Fee Record\n";
                    cout << "5. View All Fee Records\n";
                    cout << "6. Check Fee Due\n";
                    cout << "7. Back to Main Menu\n";
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
                            int id = getValidatedInt("Enter Student ID: ");
                            string name = getValidatedString("Enter Name: ");
                            int total = getValidatedInt("Enter Total Fee: ");
                            int paid = getValidatedInt("Enter Fee Paid: ");
                            int security = getValidatedInt("Enter Security Fee: ");
                            string date = getValidatedString("Enter Payment Date: ");
                            fm.Add(id, name, total, paid, security, date);
                            break;
                        }
                        case 2: {
                            int id = getValidatedInt("Enter Student ID to delete: ");
                            fm.Delete(id);
                            break;
                        }
                        case 3: {
                            int id = getValidatedInt("Enter Student ID to update total fee: ");
                            int total = getValidatedInt("Enter new Total Fee: ");
                            fm.Update(id, total);
                            break;
                        }
                        case 4: {
                            int id = getValidatedInt("Enter Student ID to search: ");
                            fm.Search(id);
                            break;
                        }
                        case 5:
                            fm.displayAllFeeRecords();
                            break;
                        case 6: {
                            int id = getValidatedInt("Enter Student ID to check due: ");
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
                    cout << "\n-- Mess Attendance Menu --\n";
                    cout << "1. Add Attendance\n";
                    cout << "2. Delete Attendance\n";
                    cout << "3. View All Attendance\n";
                    cout << "4. Search Attendance by Student ID\n";
                    cout << "5. Back to Main Menu\n";
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
                            int studentId = getValidatedInt("Enter Student ID: ");
                            string date = getValidatedString("Enter Date (YYYY-MM-DD): ");
                            string meal = getValidatedString("Enter Meal Type (breakfast/lunch/dinner): ");
                            mam.Enqueue(studentId, date, meal);
                            break;
                        }
                        case 2:
                            mam.Dequeue();
                            break;
                        case 3:
                            mam.ViewAll();
                            break;
                        case 4: {
                            int id = getValidatedInt("Enter Student ID to search attendance: ");
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

            case 4: {
                int choice;
                do {
                    cout << "\n-- Room Management Menu --\n";
                    cout << "1. Add Room\n";
                    cout << "2. Delete Room\n";
                    cout << "3. Assign Student to Room\n";
                    cout << "4. Remove Student from Room\n";
                    cout << "5. View All Rooms\n";
                    cout << "6. Back to Main Menu\n";
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
                            Room* newRoom = new Room();
                            newRoom->roomId = getValidatedInt("Enter Room ID: ");
                            newRoom->roomType = getValidatedString("Enter Room Type (Single/Shared): ");
                            newRoom->capacity = getValidatedInt("Enter Capacity: ");
                            room.addRoom(newRoom);
                            break;
                        }
                        case 2: {
                            int id = getValidatedInt("Enter Room ID to delete: ");
                            room.deleteRoom(id);
                            break;
                        }
                        case 3: {
                            int roomId = getValidatedInt("Enter Room ID: ");
                            int studentId = getValidatedInt("Enter Student ID to assign: ");
                            room.assignStudentToRoom(roomId, studentId);
                            break;
                        }
                        case 4: {
                            int roomId = getValidatedInt("Enter Room ID: ");
                            int studentId = getValidatedInt("Enter Student ID to remove: ");
                            room.removeStudentFromRoom(roomId, studentId);
                            break;
                        }
                        case 5:
                            room.viewRooms();
                            break;
                        case 6:
                            cout << "Returning to main menu...\n";
                            break;
                        default:
                            cout << "Invalid option. Try again.\n";
                    }
                } while (choice != 6);
                break;
            }

            case 5:
                cout << "Exiting Program... Goodbye!\n";
                break;

            default:
                cout << "Invalid main menu choice. Try again.\n";
        }

    } while (mainChoice != 5);

    return 0;
}
