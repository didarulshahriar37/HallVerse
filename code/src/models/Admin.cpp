#include "Admin.h"

using namespace std;
// Default constructor: Initializes empty admin object
Admin::Admin(){}

// Parameterized constructor: Creates admin with ID and name
Admin::Admin(
    string adminId, 
    string name
){
    this->adminID = adminId;
    this->name = name;
}