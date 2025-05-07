#include <iostream>
#include <vector>
#include <string>
using namespace std;

class FeeRecord {
public:
    int studentID;
    string studentName;
    float feeAmount;

    FeeRecord(int id, string name, float fee) {
        studentID = id;
        studentName = name;
        feeAmount = fee;
    }

    void displayFeeRecord() {
        cout << "Student ID: " << studentID << endl;
        cout << "Student Name: " << studentName << endl;
        cout << "Fee Amount: " << feeAmount << endl;
    }
};

class FeeManagement {
private:
    vector<FeeRecord> records;

public:
    void Add(int id, string name, float fee) {
        records.push_back(FeeRecord(id, name, fee));
        cout << "Record added successfully.\n";
    }

    void Delete(int id) {
        for (size_t i = 0; i < records.size(); i++) {
            if (records[i].studentID == id) {
                records.erase(records.begin() + i);
                cout << "Record deleted successfully.\n";
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void Update(int id, float updateFee) {
        for (auto &rec : records) {
            if (rec.studentID == id) {
                rec.feeAmount = updateFee;
                cout << "Fee updated successfully.\n";
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void Search(int id) {
        for (auto &rec : records) {
            if (rec.studentID == id) {
                rec.displayFeeRecord();
                return;
            }
        }
        cout << "Record not found.\n";
    }

    void View() {
        if (records.empty()) {
            cout << "No records found.\n";
            return;
        }
        for (auto &rec : records) {
            rec.displayFeeRecord();
        }
    }
};

int main() {
    FeeManagement manager;

    manager.Add(1, "Ali", 12000);
    manager.Add(2, "Fatima", 13500);
    manager.View();

    manager.Update(1, 12500);
    manager.Search(1);

    manager.Delete(2);
    manager.View();

    return 0;
}
