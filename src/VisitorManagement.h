#ifndef VISITOR_MANAGEMENT_H
#define VISITOR_MANAGEMENT_H

#include <string>
#include "../Database/json.hpp"
using namespace std;
using json = nlohmann::json;

class StudentManagement; // Forward declaration

class VisitorManagement {
private:
    struct VisitorNode {
        int visitorID;
        int studentID;
        string visitorName;
        string purpose;
        string visitDate;
        VisitorNode* next;

        json toJson() const {
            return json{
                {"visitorID", visitorID},
                {"studentID", studentID},
                {"visitorName", visitorName},
                {"purpose", purpose},
                {"visitDate", visitDate}
            };
        }

        void fromJson(const json& j) {
            visitorID = j.at("visitorID").get<int>();
            studentID = j.at("studentID").get<int>();
            visitorName = j.at("visitorName").get<string>();
            purpose = j.at("purpose").get<string>();
            visitDate = j.at("visitDate").get<string>();
        }
    };

    VisitorNode* head;
    int nextVisitorID;              // Auto-incrementing ID
    StudentManagement* sm;         // Pointer to StudentManagement for ID verification

public:
    VisitorManagement(StudentManagement* sm);
    ~VisitorManagement();

    void Add(int studentID, const string& name, const string& purpose, const string& date);
    void Delete(int visitorID);
    void Update(int visitorID, const string& newName, const string& newPurpose, const string& newDate);
    void Search(int visitorID);
    void View();
    bool exists(int visitorId);

    // JSON file handling
    void saveVisitorsToFile(const string& filename);
    void loadVisitorsFromFile(const string& filename);
    void updateVisitorInFile(const string& filename, int visitorID);
    void deleteVisitorFromFile(const string& filename, int visitorID);
};

#endif
