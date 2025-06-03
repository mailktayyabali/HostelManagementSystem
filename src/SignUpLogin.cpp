#include <iostream>
#include <string>
using namespace std;

class SignUpLogin {
private:
int MAX_USERS = 100;
string usernames[100];
string passwords[100];
string emails[100];
string phones[100];

int userCount = 0;
    bool usernameExists(string uname) {
        for (int i = 0; i < userCount; i++) {
            if (usernames[i] == uname)
                return true;
        }
        return false;
    }
    bool isValidPassword(string pwd) {
        if (pwd.length() < 8) return false;

        for (int i = 0; i < (int)pwd.length(); i++) {
            if (!isalnum(pwd[i]))  
                return true;
        }
        return false;  
    }
public:
    void SignUp() {
        if (userCount == MAX_USERS) {
            cout << "User limit reached!\n";
            return;
        }
        string uname, pwd, email, phone;
        cout << "Enter username: ";
        cin >> uname;
        if (usernameExists(uname)) {
            cout << "Username already exists! Try a different one.\n";
            return;
        }
        while (true) {
            cout << "Enter password (min 8 chars, at least one special character): ";
            cin >> pwd;
            if (isValidPassword(pwd)) {
                break;
            }
            else {
                cout << "Password does not meet requirements. Please try again.\n";
            }
        }
        cout << "Enter email: ";
        cin >> email;
        cout << "Enter phone number: ";
        cin >> phone;
        usernames[userCount] = uname;
        passwords[userCount] = pwd;
        emails[userCount] = email;
        phones[userCount] = phone;
        userCount++;
        cout << "Sign up successful!\n";
    }

    void Login() {
        string uname, pwd;
        while (true) {
            cout << "Enter username: ";
            cin >> uname;
            cout << "Enter password: ";
            cin >> pwd;
            bool found = false;
            for (int i = 0; i < userCount; i++) {
                if (usernames[i] == uname && passwords[i] == pwd) {
                    cout << "Login successful!\n";
                    found = true;
                    break;
                }
            }
            if (found) break;
            else cout << "Not able to login due to wrong credentials. Please enter right credentials.\n";
        }
    }
};

// int main() {
//     SignUpLogin auth;
//     int choice;

//     while (true) {
//         cout << "\n1. Sign Up\n2. Login\n3. Exit\nChoose option: ";
//         cin >> choice;

//         if (choice == 1) {
//             auth.SignUp();
//         }
//         else if (choice == 2) {
//             auth.Login();
//         }
//         else if (choice == 3) {
//             cout << "Exiting...\n";
//             break;
//         }
//         else {
//             cout << "Invalid choice, try again.\n";
//         }
//     }
//     return 0;
// }
