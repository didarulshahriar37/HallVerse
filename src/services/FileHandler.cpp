#include "FileHandler.h"

#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

// Constructor: initialize file paths
FileHandler::FileHandler() {
    studentFile = "data/students.csv";
    adminFile = "data/admins.csv";
    complaintFile = "data/complaints.csv";
    workerFile = "data/workers.csv";
    assignmentFile = "data/assignments.csv";
    entryExitFile = "data/entry_exit.csv";
}

// ====================== STUDENT FILE ======================

// Read students from CSV and return Student objects
vector<Student> FileHandler::readStudents() {
    vector<Student> students;
    ifstream file(studentFile);

    if (!file.is_open()) {
        cout << "[FileHandler] students.csv not found. Using empty list.\n";
        return students;
    }

    string line;
    getline(file, line); // skip header

    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string studentID, name, email, emergencyContact, roomNumber, duesStr;

        getline(ss, studentID, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');
        getline(ss, emergencyContact, ',');
        getline(ss, roomNumber, ',');
        getline(ss, duesStr, ',');

        double hallDues = 0.0;
        try {
            hallDues = stod(duesStr);
        } catch (...) {
            hallDues = 0.0;
        }

        Student s(studentID, name, email,
                  emergencyContact, roomNumber, hallDues);

        students.push_back(s);
    }

    file.close();
    return students;
}

// Write Student objects back to CSV
void FileHandler::writeStudents(const vector<Student>& students) {
    ofstream file(studentFile);

    if (!file.is_open()) {
        cout << "[FileHandler] Error opening students.csv for writing.\n";
        return;
    }

    // Write CSV header
    file << "studentID,name,email,emergencyContact,roomNumber,hallDues\n";

    for (size_t i = 0; i < students.size(); i++) {
        file << students[i].getStudentID() << ","
             << students[i].getName() << ","
             << students[i].getEmail() << ","
             << students[i].getEmergencyContact() << ","
             << students[i].getRoomNumber() << ","
             << students[i].getHallDues() << "\n";
    }

    file.close();
}
