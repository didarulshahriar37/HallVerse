#include "AuthenticationManager.h"

// Constructor implementation: Initializes authentication manager with file handling and hashing services
// Parameters: fileHandler - service for reading/writing user credentials
//           hasher - service for password hashing
// Features used: User authentication system, password security
AuthenticationManager::AuthenticationManager(FileHandler* fileHandler, Hasher* hasher) {
    this->fileHandler = fileHandler;
    this->hasher = hasher;
}

// Login implementation: Authenticates user login by verifying username/password against stored credentials
// Parameters: username - user ID to authenticate
//           password - plain text password to verify
//           isAdmin - true for admin login, false for student login
// Returns: true if authentication successful, false otherwise
// Features used: Login system, credential verification, admin/student access control
bool AuthenticationManager::login(const string& username, const string& password, bool isAdmin) {
    string passwordHash = hasher->hash(password);
    return fileHandler->checkCredentials(username, passwordHash, isAdmin);
}

// Reset password implementation: Resets user password by updating the hash in the credential file
// Parameters: username - user ID whose password to reset
//           newPassword - new plain text password
//           isAdmin - true for admin, false for student
// Features used: Password reset functionality, credential management
void AuthenticationManager::resetPassword(const string& username, const string& newPassword, bool isAdmin) {
    string newPasswordHash = hasher->hash(newPassword);
    fileHandler->updatePassword(username, newPasswordHash, isAdmin);
}