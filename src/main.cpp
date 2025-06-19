#include <iostream>
#include "StudentManagement.h"
#include "FeeManagement.h"
#include "MessAttendanceManagement.h"
#include "Room.h"
#include "VisitorManagement.h"
#include "Validate.h"
#include "LoginSystem.h"
#include <cstdlib>
#include <chrono>
#include <thread>

using namespace std;

int main() {
    LoginSystem auth;
    if (!auth.adminExists()) {
    cout << " No admin found. Please register first.\n";
    auth.registerAdmin();
    }
    bool loggedIn = false;
    for (int i = 0; i < 3 && !loggedIn; ++i) {
        loggedIn = auth.login();
        if (!loggedIn) cout << "Try again...\n";
    }
    if (!loggedIn) {
    cout << " Too many failed attempts. Exiting...\n";
    return 0;
    }

    StudentManagement sm;
    FeeManagement fm(&sm);  
    MessAttendanceManagement mam(&sm);
    RoomManagement room(sm);
    VisitorManagement vm(&sm);

    int mainChoice;
    room.loadRoomsFromFile("rooms.json"); // Load rooms from file at startup
    sm.loadStudentsFromFile("students.json"); // Load students from file at startup
    fm.loadFeesFromFile("fees.json"); // Load fees from file at startup
    vm.loadVisitorsFromFile("visitors.json"); // Load visitors from file at startup
    // mam.loadAttendanceFromFile("attendance.json");// Load attendance from file at startup
    
    do {        
        system("cls");
        cout << "=======================================================================\n";
        cout << "                     HOSTEL MANAGEMENT SYSTEM\n";  
        cout << "=======================================================================\n";
        cout << "Welcome to the Hostel Management System!\n";
        
        cout << "1. Student Management\n";
        cout << "2. Fee Management\n";
        cout << "3. Mess Attendance Management\n";
        cout << "4. Room Management\n";
        cout << "5. Visitor Management\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> mainChoice;

        if (cin.fail()) {
            cin.clear();
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
                            int studentId;
                            while (true) {
                                studentId = getValidatedInt("Enter ID: ");
                                if (sm.exists(studentId)) {
                                    cout << "This ID already exists! Please enter a different ID.\n";
                                } else {
                                    break;
                                }
                            }
                            Student* newStudent = new Student();
                            newStudent->studentId = studentId;
                            while (sm.exists(newStudent->studentId)) {
                                cout << "This ID already exists! Please enter a different ID.\n";
                                newStudent->studentId = getValidatedInt("Enter ID: ");
                            }
                            newStudent->studentName = getValidatedString("Enter Name: ");
                            newStudent->CNIC = getValidatedCNIC("Enter CNIC (e.g., 12345-1234567-1): ");
                            newStudent->studentAddress = getValidatedString("Enter Address: ");
                            newStudent->studentPhone = getValidatedPhone("Enter Phone: ");
                            sm.addStudent(newStudent);
                            sm.saveStudentsToFile("students.json");
                            break;
                        }
                        case 2: {
                            int id = getValidatedInt("Enter Student ID to delete: ");
                            while (!sm.exists(id)) {
                                cout << "Student not found! Please enter a valid Student ID: ";
                                id = getValidatedInt("");
                            }
                            sm.deleteStudent(id);
                            sm.deleteStudentFromFile("students.json",id);
                            break;
                        }
                        case 3: {
                            int id = getValidatedInt("Enter Student ID to update: ");
                            while (!sm.exists(id)) {
                                cout << "Student not found! Please enter a valid Student ID: ";
                                id = getValidatedInt("");
                            }
                            Student* updatedStudent = new Student();
                            updatedStudent->studentId = id;
                            updatedStudent->studentName = getValidatedString("Enter New Name: ");
                            updatedStudent->CNIC = getValidatedCNIC("Enter New CNIC: ");
                            updatedStudent->studentAddress = getValidatedString("Enter New Address: ");
                            updatedStudent->studentPhone = getValidatedPhone("Enter New Phone: ");
                            sm.updateStudent(id, updatedStudent);
                            sm.updateStudentInFile("students.json",id, *updatedStudent );
                            delete updatedStudent;
                            break;
                        }
                        case 4:
                            sm.loadStudentsFromFile("students.json"); // Load students from file before viewing
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
        cout << "3. Update Fee Record\n";
        cout << "4. Search Fee Records by Student ID\n";
        cout << "5. Check Due Amount\n";
        cout << "6. View All Fee Records\n";
        cout << "7. Exit\n";
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
                while (!sm.exists(studentId)) {
                    cout << "Student not found! Please enter a valid Student ID: ";
                    studentId = getValidatedInt("");
                };
                int totalFee = getValidatedInt("Enter Total Fee: ");
                while (totalFee < 0) {
                    cout << "Total fee cannot be negative. Please try again.\n";
                    totalFee = getValidatedInt("Enter Total Fee: ");
                }
                int paidFee = getValidatedInt("Enter Paid Fee: ");
                while (paidFee < 0 || paidFee > totalFee) {
                    cout << "Paid fee cannot be negative or greater than total fee. Please try again.\n";
                    paidFee = getValidatedInt("Enter Paid Fee: ");
                }
                int securityFee = getValidatedInt("Enter Security Fee: ");
                while (securityFee < 0) {
                    cout << "Security fee cannot be negative. Please try again.\n";
                    securityFee = getValidatedInt("Enter Security Fee: ");
                }
                string date = getValidatedDate("Enter Date (DD-MM-YYYY): ");

                if (fm.Add(studentId, totalFee, paidFee, securityFee, date)) {
                    fm.saveFeesToFile("fees.json");
                }
                break;
            }
            case 2: {
                int studentId = getValidatedInt("Enter Student ID: ");
                while (!sm.exists(studentId)) {
                    cout << "Student not found! Please enter a valid Student ID: ";
                    studentId = getValidatedInt("");
                }
                string date = getValidatedDate("Enter Date (DD-MM-YYYY) to delete: ");

                if (fm.Delete(studentId, date)) {
                    fm.deleteFeeFromFile("fees.json", studentId, date);
                }
                break;
            }
            case 3: {
                int studentId = getValidatedInt("Enter Student ID: ");
                while (!sm.exists(studentId)) {
                    cout << "Student not found! Please enter a valid Student ID: ";
                    studentId = getValidatedInt("");
                }
                string date = getValidatedDate("Enter Date (DD-MM-YYYY) to update: ");
                int totalFee = getValidatedInt("Enter New Total Fee: ");
                while (totalFee < 0) {
                    cout << "Total fee cannot be negative. Please try again.\n";
                    totalFee = getValidatedInt("Enter New Total Fee: ");
                }
                int paidFee = getValidatedInt("Enter New Paid Fee: ");
                while (paidFee < 0 || paidFee > totalFee) {
                    cout << "Paid fee cannot be negative or greater than total fee. Please try again.\n";
                    continue;
                }
                int securityFee = getValidatedInt("Enter New Security Fee: ");
                while (securityFee < 0) {
                    cout << "Security fee cannot be negative. Please try again.\n";
                    securityFee = getValidatedInt("Enter New Security Fee: ");
                }

                if (fm.Update(studentId, totalFee, paidFee, securityFee, date)) {
                    fm.updateFeeInFile("fees.json", studentId, date);
                }
                break;
            }
            case 4: {
                int studentId = getValidatedInt("Enter Student ID to search: ");
                while (!sm.exists(studentId)) {
                    cout << "Student not found! Please enter a valid Student ID: ";
                    studentId = getValidatedInt("");
                }
                fm.Search(studentId);
                break;
            }
            case 5: {
                int studentId = getValidatedInt("Enter Student ID: ");
                while (!sm.exists(studentId)) {
                    cout << "Student not found! Please enter a valid Student ID: ";
                    studentId = getValidatedInt("");
                }
                string date = getValidatedDate("Enter Date (DD-MM-YYYY): ");
                fm.CheckDue(studentId, date);
                break;
            }
            case 6:
                fm.View();
                break;
            case 7:
                cout << "Exiting Fee Management...\n";
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
                    cout << "\n-- Mess Attendance Management Menu --\n";
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
                            while (!sm.exists(studentId)) {
                                cout << "Student not found! Please enter a valid Student ID: ";
                                studentId = getValidatedInt("");
                            }
                            string date = getValidatedDate("Enter Date (DD-MM-YYYY): ");
                            string meal;
                            while (true) {
                                meal = getValidatedString("Enter Meal Type (breakfast/lunch/dinner): ");
                                for (auto& c : meal) c = tolower(c);
                                if (meal == "breakfast" || meal == "lunch" || meal == "dinner") {
                                    break;
                                } else {
                                    cout << "Invalid meal type! Please enter only 'breakfast', 'lunch', or 'dinner'.\n"; 
                                }
                            }
                            mam.Enqueue(studentId, date, meal);
                            break;
                        }
                        case 2: {
                            int subChoice;
                            cout << "\n-- Delete Attendance --\n";
                            cout << "1. Delete by Student ID\n";
                            cout << "2. Delete by Student ID + Date + Meal Type\n";
                            cout << "Enter your choice: ";
                            cin >> subChoice;
                            if (cin.fail()) {
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cout << "Invalid input! Try again.\n";
                                continue;
                            }

                            if (subChoice ==1) {
                                int id = getValidatedInt("Enter Student ID to delete attendance: ");
                                while (!sm.exists(id)) {
                                    cout << "Student not found! Please enter a valid Student ID: ";
                                    id = getValidatedInt("");
                                }
                                mam.DeleteByStudentId(id);
                            } else if (subChoice == 2) {
                                int id = getValidatedInt("Enter Student ID: ");
                                while (!sm.exists(id)) {
                                    cout << "Student not found! Please enter a valid Student ID: ";
                                    id = getValidatedInt("");
                                }
                                string date = getValidatedDate("Enter Date (DD-MM-YYYY): ");
                                string meal;
                                while (true) {
                                    meal = getValidatedString("Enter Meal Type (breakfast/lunch/dinner): ");
                                    if (meal == "breakfast" || meal == "lunch" || meal == "dinner") break;
                                    cout << "Invalid meal type! Use breakfast/lunch/dinner.\n";
                                }
                                mam.DeleteByDateAndMeal(id, date, meal);
                            } else {
                                cout << "Invalid deletion option!\n";
                            }
                            break;
                        }
                        case 3:
                            mam.ViewAll();
                            break;
                        case 4: {
                            int id = getValidatedInt("Enter Student ID to search attendance: ");
                            while (!sm.exists(id)) {
                                cout << "Student not found! Please enter a valid Student ID: ";
                                id = getValidatedInt("");
                            }
                            mam.Search(id);
                            break;
                        }
                        case 5:
                            cout << "Returning to main menu...\n";
                            break;
                        default:
                            cout << "Invalid choice. Please try again.\n";
                    }
                } while (choice !=5);
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
                            int roomId;
                            while (true) {
                                roomId = getValidatedInt("Enter Room ID: ");
                                if (room.exists(roomId)) {
                                    cout << "This Room ID already exists! Please enter a different Room ID.\n";
                                } else {
                                    break;
                                }
                            }
                            Room* newRoom = new Room();
                            newRoom->roomId = roomId;
                            newRoom->roomType = getValidatedString("Enter Room Type (Single/Shared): ");
                            newRoom->capacity = getValidatedInt("Enter Capacity: ");
                            room.addRoom(newRoom);
                            room.saveRoomsToFile("rooms.json"); // Save rooms to file after adding
                            break;
                        }
                        case 2: {
                            int id = getValidatedInt("Enter Room ID to delete: ");
                            room.deleteRoom(id);
                            room.deleteRoomFromFile("rooms.json", id); // Delete from file
                            break;
                        }
                        case 3: {
                            int roomId = getValidatedInt("Enter Room ID: ");
                            while (!room.exists(roomId)) {
                                cout << "Room not found! Please enter a valid Room ID: ";
                                roomId = getValidatedInt("");
                            }
                            int studentId = getValidatedInt("Enter Student ID to assign: ");
                            while(!sm.exists(studentId)){
                                cout << "Student not found! Please enter a valid Student ID: ";
                                studentId = getValidatedInt("");
                            }
                            room.assignStudentToRoom(roomId, studentId);
                            room.updateRoomInFile("rooms.json", roomId); // Update room in file after assigning student
                            break;
                        }
                        case 4: {
                            int roomId = getValidatedInt("Enter Room ID: ");

                            int studentId = getValidatedInt("Enter Student ID to remove: ");
                            room.removeStudentFromRoom(roomId, studentId);
                            room.updateRoomInFile("rooms.json", roomId); // Update room in file after removing student
                            break;
                        }
                        case 5:
                            room.loadRoomsFromFile("rooms.json"); // Load rooms from file before viewing
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

            case 5: {
                int choice;
                do {
                    cout << "\n-- Visitor Management Menu --\n";
                    cout << "1. Add Visitor\n";
                    cout << "2. Delete Visitor\n";
                    cout << "3. Update Visitor\n";
                    cout << "4. Search Visitor by ID\n";
                    cout << "5. View All Visitors\n";
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
                           int studentID = getValidatedInt("Enter Student ID: ");
                            while (!sm.exists(studentID)) {
                                cout << "Student not found! Please enter a valid Student ID: ";
                                studentID = getValidatedInt("");
                            }
                           string name = getValidatedString("Enter Visitor Name: ");
                            string purpose = getValidatedString("Enter Purpose of Visit: ");
                            string date = getValidatedDate("Enter Visit Date (DD-MM-YYYY): ");
                            vm.Add(studentID, name, purpose, date);
                            vm.saveVisitorsToFile("visitors.json"); // Save visitors to file after adding
                            break;
                        }
                         case 2: {
                            int visitorID = getValidatedInt("Enter Visitor ID to delete: ");
                            while (!vm.exists(visitorID)) {
                                cout << "Visitor not found! Please enter a valid Visitor ID: ";
                                visitorID = getValidatedInt("");
                            }
                            vm.Delete(visitorID);
                            vm.deleteVisitorFromFile("visitors.json", visitorID); // Delete from file
                            break;
                        }
                        case 3: {
                            int visitorID = getValidatedInt("Enter Visitor ID to update: ");
                            while (!vm.exists(visitorID)) {
                                cout << "Visitor not found! Please enter a valid Visitor ID: ";
                                visitorID = getValidatedInt("");
                            }
                            string newName = getValidatedString("Enter New Name: ");
                            string newPurpose = getValidatedString("Enter New Purpose: ");
                            string newDate = getValidatedDate("Enter New Date (DD-MM-YYYY): ");
                            vm.Update(visitorID, newName, newPurpose, newDate);
                            vm.updateVisitorInFile("visitors.json", visitorID); // Update in file
                            break;
                        }
                        case 4: {
                            int visitorID = getValidatedInt("Enter Visitor ID to search: ");
                            vm.Search(visitorID);
                            break;
                        }
                        case 5:
                            vm.View();
                            break;
                        case 6:
                            cout << "Returning to main menu...\n";
                            break;
                        default:
                            cout << "Invalid choice. Try again.\n";
                    }
                } while (choice != 6);
                    break;
            }
            case 6:
                cout << "Exiting Program... Goodbye!\n";
                break;

            default:
                cout << "Invalid main menu choice. Try again.\n";
               
        }

    } while (mainChoice != 6);

    return 0;
}