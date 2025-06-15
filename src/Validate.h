#ifndef VALIDATE_H
#define VALIDATE_H

#include <string>

int getValidatedInt(const std::string& prompt);
std::string getValidatedString(const std::string& prompt);
std::string getValidatedCNIC(const std::string& prompt);
std::string getValidatedPhone(const std::string& prompt);
std::string getValidatedDate(const std::string& prompt);

#endif
