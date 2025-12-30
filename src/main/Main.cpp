// JUST FOR TESTING

#include <iostream>
#include "../models/Admin.h"
#include "../models/Student.h"

using namespace std;

int main(){
    Admin admin;

    Student s1("230042103", "Muntajim Rahman Saimon", "saminon@123.com", "0123456789", "A101", 0);
    Student s2("230042112", "Ifham", "Ifham@123.com", "0123456789", "A102", 0);
    Student s3("230042137", "Didarul", "Didarul@123.com", "0123456789", "A101", 0);

    admin.addStudent(s1);
    admin.addStudent(s3);

    admin.addStudent(s1);
    admin.addStudent(s2);

    admin.removeStudent(s3.getStudentID());
    // admin.addStudent(s3);

    admin.viewAllStudents();

    return 0;
}