#include "AuthenticationManager.h"

AuthenticationManager::AuthenticationManager(FileHandler* fileHandler, Hasher* hasher) {
    this->fileHandler = fileHandler;
    this->hasher = hasher;
}

bool AuthenticationManager::login(const string& username, const string& password, bool isAdmin) {
    string passwordHash = hasher->hash(password);
    return fileHandler->checkCredentials(username, passwordHash, isAdmin);
}

void AuthenticationManager::resetPassword(const string& username, const string& newPassword, bool isAdmin) {
    string newPasswordHash = hasher->hash(newPassword);
    fileHandler->updatePassword(username, newPasswordHash, isAdmin);
}