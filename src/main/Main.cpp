// TESTING PURPOSE (FOR NOW)
// Test 1: Adding data to students.csv file
// Test 2: Removing data from students.csv file
// Test 3: Reading data from students.csv file

#include <iostream>
#include "../models/Admin.h"
#include "../models/Student.h"

using namespace std;

int main(){
    Admin admin;
    string studentID, name, email, emergency, room;
    double hallDues;

    // cout << "Student ID: ";
    // getline(cin, studentID);

    // cout << "Name: ";
    // getline(cin, name);

    // cout << "Email: ";
    // getline(cin, email);

    // cout << "Emergency: ";
    // getline(cin, emergency);

    // cout << "Room: ";
    // getline(cin, room);

    // cout << "Hall Dues: ";
    // cin >> hallDues;

    // Student student(studentID, name, email, emergency, room, hallDues);

    // admin.addStudent(student);

    cout << "Enter student ID to remove: ";
    getline(cin, studentID);

    admin.removeStudent(studentID);

    // admin.viewAllStudents();

    return 0;
}