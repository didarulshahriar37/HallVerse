#ifndef ADMIN_H
#define ADMIN_H
#include<string>

class Admin{
    
    // Variables
    private:
    string adminID;
    string name;

    // Constructors
    public:
    Admin();
    Admin(string adminId, string name);

    // Getters
    string getAdminID() const {
        return adminID;
    };
    string getName() const {
        return name;
    };
};

#endif