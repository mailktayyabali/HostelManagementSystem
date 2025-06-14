#ifndef SIGNUPLOGIN_H
#define SIGNUPLOGIN_H

#include <string>
using namespace std;

class SignUpLogin {
private:
    static const int MAX_USERS = 100;
    string usernames[MAX_USERS];
    string passwords[MAX_USERS];
    string emails[MAX_USERS];
    string phones[MAX_USERS];
    int userCount;

    bool usernameExists(const string& uname);
    bool isValidPassword(const string& pwd);
    string getMaskedPassword();

public:
    SignUpLogin();        
    void SignUp();
    bool Login();
};

#endif
