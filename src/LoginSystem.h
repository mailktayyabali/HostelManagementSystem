#ifndef LOGIN_SYSTEM_H
#define LOGIN_SYSTEM_H
#include <iostream>
#include <string>
#include <fstream>
#include "../Database/json.hpp" // Include nlohmann/json
using namespace std;
using json = nlohmann::json;

class LoginSystem {
public:
    bool adminExists();
    void registerAdmin();
    bool login();

private:
    const string filename = "admin.json";
    bool validateCredentials(const string& username, const string& password);
};

#endif
