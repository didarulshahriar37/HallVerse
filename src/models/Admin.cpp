#include "Admin.h"

using namespace std;
Admin::Admin(){}

Admin::Admin(
    string adminId, 
    string name
){
    this->adminID = adminId;
    this->name = name;
}