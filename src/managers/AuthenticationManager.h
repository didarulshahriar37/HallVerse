#ifndef AUTHENTICATION_MANAGER_H
#define AUTHENTICATION_MANAGER_H

#include <string>
#include "../services/FileHandler.h"
#include "../services/Hasher.h"

using namespace std;

class AuthenticationManager {
    private:
    FileHandler* fileHandler;
    Hasher* hasher;

    public:
    AuthenticationManager(FileHandler* fileHandler, Hasher* hasher);
    bool login(const string& username, const string& password, bool isAdmin);
    void resetPassword(const string& username, const string& newPassword, bool isAdmin);
};

#endif