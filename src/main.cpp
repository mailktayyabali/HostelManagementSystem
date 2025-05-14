#include <iostream>
#include "studentManagement.cpp"
#include "FeeManagement.cpp"

using namespace std;

int main() {
    studentManagement sm;
    FeeManagement fm;
    int choice;

    do {
        cout << "\n===== Main Menu =====" << endl;
        cout << "1. Student Management" << endl;
        cout << "2. Fee Management" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int sChoice;
                do {
                    cout << "\n-- Student Management --" << endl;
                    cout << "1. Add Student" << endl;
                    cout << "2. Delete Student" << endl;
                    cout << "3. Update Student" << endl;
                    cout << "4. View Students" << endl;
                    cout << "5. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> sChoice;

                    switch (sChoice) {
                        case 1: {
                            Student* newStudent = new Student;
                            cout << "Enter Student ID: ";
                            cin >> newStudent->studentId;
                            cin.ignore(); // Corrected position
                            cout << "Enter Student Name: ";
                            getline(cin, newStudent->studentName);
                            cout << "Enter CNIC: ";
                            cin >> newStudent->CNIC;
                            cin.ignore();
                            cout << "Enter Address: ";
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
                            if (!sm.exists(studentId)) {
                                cout << "Student not found!" << endl;
                                break;
                            }
                            Student* updatedStudent = new Student;
                            cin.ignore(); // Corrected position
                            cout << "Enter Updated Student Name: ";
                            getline(cin, updatedStudent->studentName);
                            cout << "Enter Updated CNIC: ";
                            cin >> updatedStudent->CNIC;
                            cin.ignore();
                            cout << "Enter Updated Address: ";
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
                            break;
                        default:
                            cout << "Invalid choice!\n";
                    }
                } while (sChoice != 5);
                break;
            }

            case 2: {
                int fChoice;
                do {
                    cout << "\n-- Fee Management --" << endl;
                    cout << "1. Add Fee Record" << endl;
                    cout << "2. Delete Fee Record" << endl;
                    cout << "3. Update Total Fee" << endl;
                    cout << "4. Search Fee Record" << endl;
                    cout << "5. View All Fee Records" << endl;
                    cout << "6. Add Fee Payment" << endl;
                    cout << "7. Check Fee Due" << endl;
                    cout << "8. Update Fee Paid" << endl;
                    cout << "9. Back to Main Menu" << endl;
                    cout << "Enter your choice: ";
                    cin >> fChoice;

                    switch (fChoice) {
                        case 1: {
                            int id, total, paid, security;
                            string name, date;
                            cout << "Enter Student ID: ";
                            cin >> id;
                            if (!sm.exists(id)) { // ✅ Check if student exists
                                cout << "Student ID not found. Add student first!" << endl;
                                break;
                            }
                            cin.ignore();
                            cout << "Enter Name: ";
                            getline(cin, name);
                            cout << "Enter Total Fee: ";
                            cin >> total;
                            cout << "Enter Fee Paid: ";
                            cin >> paid;
                            cout << "Enter Security Fee: ";
                            cin >> security;
                            cin.ignore();
                            cout << "Enter Payment Date: ";
                            getline(cin, date);
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
                            int id, amount;
                            string date;
                            cout << "Enter Student ID to add payment: ";
                            cin >> id;
                            cout << "Enter Amount Paid: ";
                            cin >> amount;
                            cin.ignore();
                            cout << "Enter Payment Date: ";
                            getline(cin, date);
                            fm.addFee(id, amount, date);
                            break;
                        }
                        case 7: {
                            int id;
                            cout << "Enter Student ID to check due: ";
                            cin >> id;
                            fm.checkDue(id);
                            break;
                        }
                        case 8: {
                            int id, amount;
                            string date;
                            cout << "Enter Student ID to update fee paid: ";
                            cin >> id;
                            cout << "Enter New Amount Paid: ";
                            cin >> amount;
                            cin.ignore();
                            cout << "Enter Payment Date: ";
                            getline(cin, date);
                            fm.updatePayment(id, amount, date);
                            break;
                        }
                        case 9:
                            break;
                        default:
                            cout << "Invalid choice!\n";
                    }
                } while (fChoice != 9);
                break;
            }

            case 3:
                cout << "Thank you for using the Hostel Management System. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice! Please try again.\n";
        }

    } while (choice != 3);

    return 0;
}
