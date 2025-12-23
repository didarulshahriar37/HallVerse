#include "FileHandler.h"
#include <fstream>

using namespace std;

FileHandler::FileHandler() {
    studentFile = "data/students.csv";
    adminFile = "data/admins.csv";
    complaintFile = "data/complaints.csv";
    workerFile = "data/workers.csv";
    assignmentFile = "data/assignments.csv";
    entryExitFile = "data/entry_exit.csv";
}

vector<string> FileHandler::readStudents() {
    vector<string> data;
    ifstream file(studentFile);
    string line;
    while (getline(file, line)) {
        data.push_back(line);
    }
    return data;
}

void FileHandler::writeStudents(const vector<string>& data) {
    ofstream file(studentFile);
    for (auto line : data) {
        file << line << endl;
    }
}

vector<string> FileHandler::readAdmins() {
    vector<string> data;
    ifstream file(adminFile);
    string line;
    while (getline(file, line)) {
        data.push_back(line);
    }
    return data;
}

vector<string> FileHandler::readComplaints() {
    vector<string> data;
    ifstream file(complaintFile);
    string line;
    while (getline(file, line)) {
        data.push_back(line);
    }
    return data;
}

void FileHandler::writeComplaints(const vector<string>& data) {
    ofstream file(complaintFile);
    for (auto line : data) {
        file << line << endl;
    }
}

vector<string> FileHandler::readWorkers() {
    vector<string> data;
    ifstream file(workerFile);
    string line;
    while (getline(file, line)) {
        data.push_back(line);
    }
    return data;
}

void FileHandler::writeWorkers(const vector<string>& data) {
    ofstream file(workerFile);
    for (auto line : data) {
        file << line << endl;
    }
}

vector<string> FileHandler::readAssignments() {
    vector<string> data;
    ifstream file(assignmentFile);
    string line;
    while (getline(file, line)) {
        data.push_back(line);
    }
    return data;
}

void FileHandler::writeAssignments(const vector<string>& data) {
    ofstream file(assignmentFile);
    for (auto line : data) {
        file << line << endl;
    }
}

vector<string> FileHandler::readEntryExitLogs() {
    vector<string> data;
    ifstream file(entryExitFile);
    string line;
    while (getline(file, line)) {
        data.push_back(line);
    }
    return data;
}

void FileHandler::writeEntryExitLogs(const vector<string>& data) {
    ofstream file(entryExitFile);
    for (auto line : data) {
        file << line << endl;
    }
}
