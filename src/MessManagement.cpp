#include <iostream>
#include <string>
using namespace std;

class node
{
public:
    int studentId;
    string studentName;
    int date;
    node *next;


    node(int id, string n, int d)
    {
        studentId = id;
        studentName = n;
        date = d;
        next = nullptr;
    }
};

class MessAttendance
{
    node *head;

public:
    MessAttendance()
    {
        head = nullptr;
    }
    
    void Add(int id, string name, int date){
        node* newNode = new node(id , name , date);
        if(head == nullptr){
            head = newNode;
            return;
        }

        node* temp = head;
        while(temp->next !=nullptr){
            temp = temp->next;
            
        }
        temp->next = newNode;

    }

    void View() {
        node* temp = head;
        if (!temp) {
            cout << "No attendance records found.\n";
            return;
        }
    
        cout << "Mess Attendance Records:\n";
        while (temp != nullptr) {
            cout << "ID: " << temp->studentId << ", Name: " << temp->studentName << ", Date: " << temp->date << endl;
            temp = temp->next;
        }
    }
    

    void Search(int id) {
        node* temp = head;
        while (temp != nullptr) {
            if (temp->studentId == id) {
                cout << "Record Found:\n";
                cout << "ID: " << temp->studentId << ", Name: " << temp->studentName << ", Date: " << temp->date << endl;
                return;
            }
            temp = temp->next;
        }
        cout << "No record found with ID " << id << ".\n";
    }
    

    void Update(int id){

    }
    
    void Deleteatlast(){
     if (head == nullptr)
     {
        cout<<"No Records found to delete!"<<endl;
        return;
     }

     if (head->next == nullptr)
     {
        delete head;
        head = nullptr;
        cout<<"Record Deleted successfully!"<<endl;
     }

     node* prev = nullptr;
     node* temp = head;

     while (temp->next != nullptr)
     {
        prev = temp;
        temp = temp-> next;
     }

     prev->next = nullptr;
     delete temp;
     
     cout<<"Last record deleted succesfully!";

    }

    void Display(){
        node* temp = head;
        while(temp !=nullptr){
   
            cout<<"Id : "<<temp->studentId<<endl;
            cout<<"Name  : "<<temp->studentName<<endl;
            cout<<"Date : "<<temp->date<<endl;
            cout<<endl;
            temp = temp->next;
        }
    }

};

int main() {
    MessAttendance mess;
    int choice;

    cout << "=== Mess Attendance Management ===\n";

    while (true) {
        cout << "\nMenu:\n";
        cout << "1. Add Record\n";
        cout << "2. View All Records\n";
        cout << "3. Search Record by ID\n";
        cout << "4. Delete Last Record\n";
        cout << "0. Exit\n\n";
        cout << "Enter your choice: \n";
        cin >> choice;

        if (choice == 1) {
            int id, date;
            string name;
            cout << "Enter Student ID: ";
            cin >> id;
            cin.ignore(); 
            cout << "Enter Student Name: ";
            getline(cin, name);
            cout << "Enter Date (YYYY/MM/DD): ";
            cin >> date;
            mess.Add(id, name, date);
        }
        else if (choice == 2) {
            mess.Display();
        }
        else if (choice == 3) {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            mess.Search(id);
        }
        else if (choice == 4) {
            mess.Deleteatlast();
        }
        else if (choice == 0) {
            cout << "Exiting program...\n";
            break; 
        }
        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
