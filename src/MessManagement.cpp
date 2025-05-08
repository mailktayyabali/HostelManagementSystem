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
    
    void Delete(int id){
     
        


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

int main()
{

    MessAttendance m1;
    m1.Entryatend(1 , "Hashim" , 10);
    m1.Entryatend(2 , "zia" , 10);
    m1.Entryatend(3,"Taimoor" , 11);
    m1.Display();
    return 0;
}