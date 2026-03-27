#include "FileHandler.h"
#include "../models/Student.h"
#include "../models/Complaint.h"
#include "../models/Worker.h"
#include "../models/WorkAssignment.h"
#include "../models/EntryExitRecord.h"
#include <fstream>
#include <sstream>
#include <iostream>
 
using namespace std;
// Constructor: Initializes file paths for all data files
FileHandler::FileHandler() 
    : id("FH_001"),
      studentFile("data/students.csv"),
      adminFile("data/admins.csv"),
      complaintFile("data/complaints.csv"),
      workerFile("data/workers.csv"),
      assignmentFile("data/assignments.csv"),
      entryExitFile("data/entry_exit.csv") {}

// Helper function: Splits string by delimiter for CSV parsing
vector<string> FileHandler::split(const string& str, char delimiter) {
    vector<string> tokens;
    stringstream ss(str);
    string token;
    while (getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

// Reads student data from CSV file, handles multiple formats
vector<Student> FileHandler::readStudents() {
    vector<Student> students;
    ifstream file(studentFile);
    string line;
    
    if (!file.is_open()) return students;

    getline(file, line);
    bool headerHasHallName = false;
    for (const auto& token : split(line, ',')) {
        if (token == "hallName") {
            headerHasHallName = true;
            break;
        }
    }
    while (getline(file, line)) {
        try {
            auto tokens = split(line, ',');
            // Possible formats (columns):
            // 9: id,name,email,emergencyContact,roomNumber,bedNumber,hallName,hallDues,password
            // 8: id,name,email,emergencyContact,roomNumber,bedNumber,hallDues,password
            // 7: legacy id,name,email,emergencyContact,roomNumber,hallDues,password
            if (tokens.size() >= 9) {
                double dues = 0.0;
                try { dues = stod(tokens[7]); } catch (...) { dues = 0.0; }
                Student s(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], dues);
                s.setPasswordHash(tokens[8]);
                students.push_back(s);
            } else if (tokens.size() == 8) {
                if (headerHasHallName) {
                    double dues = 0.0;
                    try { dues = stod(tokens[7]); } catch (...) { dues = 0.0; }
                    Student s(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], dues);
                    s.setPasswordHash("");
                    students.push_back(s);
                } else {
                    double dues = 0.0;
                    try { dues = stod(tokens[6]); } catch (...) { dues = 0.0; }
                    Student s(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], string(""), dues);
                    s.setPasswordHash(tokens[7]);
                    students.push_back(s);
                }
            } else if (tokens.size() >= 7) {
                double dues = 0.0;
                try { dues = stod(tokens[5]); } catch (...) { dues = 0.0; }
                Student s(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], string(""), string(""), dues);
                s.setPasswordHash(tokens[6]);
                students.push_back(s);
            }
        } catch (const exception& e) {
            cerr << "Error parsing student line: " << e.what() << endl;
        }
    }
    file.close();
    return students;
}

// Writes student data to CSV file with header
void FileHandler::writeStudents(const vector<Student>& students) {
    ofstream file(studentFile);
    file << "studentID,name,email,emergencyContact,roomNumber,bedNumber,hallName,hallDues,password\n";
    for (const auto& s : students) {
        file << s.getStudentID() << "," << s.getName() << "," << s.getEmail() << ","
             << s.getEmergencyContact() << "," << s.getRoomNumber() << ","
             << s.getBedNumber() << "," << s.getHallName() << "," << s.getHallDues() << "," << s.getPasswordHash() << "\n";
    }
    file.close();
}

// Reads complaint data from CSV file
vector<Complaint> FileHandler::readComplaints() {
    vector<Complaint> complaints;
    ifstream file(complaintFile);
    string line;
    
    if (!file.is_open()) return complaints;
    
    getline(file, line);
    while (getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 6) {
            complaints.push_back(Complaint(tokens[0], tokens[2], tokens[3], 
                                         tokens[4], tokens[5], tokens[1]));
        }
    }
    file.close();
    return complaints;
}

// Writes complaint data to CSV file
void FileHandler::writeComplaints(const vector<Complaint>& complaints) {
    ofstream file(complaintFile);
    file << "complaintID,studentID,category,description,status,date\n";
    for (const auto& c : complaints) {
        file << c.getComplaintID() << "," << c.getStudentID() << "," 
             << c.getCategory() << "," << c.getDescription() << "," 
             << c.getStatus() << "," << c.getDate() << "\n";
    }
    file.close();
}

// Reads worker data from CSV file
vector<Worker> FileHandler::readWorkers() {
    vector<Worker> workers;
    ifstream file(workerFile);
    string line;
    
    if (!file.is_open()) return workers;
    
    getline(file, line);
    while (getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 5) {
            // Handle different representations of availability: "1", "true", "0", "false"
            bool avail = (tokens[3] == "1" || tokens[3] == "true" || tokens[3] == "True");
            string pwd = (tokens.size() >= 6) ? tokens[5] : "";
            workers.push_back(Worker(tokens[0], tokens[1], tokens[2], avail, tokens[4], pwd));
        }
    }
    file.close();
    return workers;
}

// Writes worker data to CSV file
void FileHandler::writeWorkers(const vector<Worker>& workers) {
    ofstream file(workerFile);
    file << "workerID,name,role,isAvailable,contactNumber,password\n";
    for (const auto& w : workers) {
        file << w.getWorkerID() << "," << w.getName() << "," << w.getRole() << ","
             << w.getIsAvailable() << "," << w.getContactNumber() << "," << w.getPasswordHash() << "\n";
    }
    file.close();
}

// Reads work assignment data from CSV file
vector<WorkAssignment> FileHandler::readAssignments() {
    vector<WorkAssignment> assignments;
    ifstream file(assignmentFile);
    string line;
    
    if (!file.is_open()) return assignments;
    
    getline(file, line);
    while (getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 5) {
            assignments.push_back(WorkAssignment(tokens[0], tokens[1], tokens[2], 
                                                tokens[3], tokens[4]));
        }
    }
    file.close();
    return assignments;
}

// Writes work assignment data to CSV file
void FileHandler::writeAssignments(const vector<WorkAssignment>& assignments) {
    ofstream file(assignmentFile);
    file << "assignmentID,complaintID,workerID,status,report\n";
    for (const auto& a : assignments) {
        file << a.getAssignmentID() << "," << a.getComplaintID() << "," 
             << a.getWorkerID() << "," << a.getStatus() << "," 
             << a.getReport() << "\n";
    }
    file.close();
}

// Reads entry/exit log data from CSV file
vector<EntryExitRecord> FileHandler::readEntryExitLogs() {
    vector<EntryExitRecord> records;
    ifstream file(entryExitFile);
    string line;
    
    if (!file.is_open()) return records;
    
    getline(file, line);
    while (getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 4) {
            records.push_back(EntryExitRecord(tokens[0], tokens[1], tokens[2], tokens[3]));
        }
    }
    file.close();
    return records;
}

// Writes entry/exit log data to CSV file
void FileHandler::writeEntryExitLogs(const vector<EntryExitRecord>& records) {
    ofstream file(entryExitFile);
    file << "recordID,studentID,type,timestamp\n";
    for (const auto& r : records) {
        file << r.getRecordID() << "," << r.getStudentID() << "," 
             << r.getType() << "," << r.getTimestamp() << "\n";
    }
    file.close();
}

// Checks if username/password hash exists in admin or student file
bool FileHandler::checkCredentials(const string& username, const string& passwordHash, bool isAdmin) {
    string filename = isAdmin ? adminFile : studentFile;
    ifstream file(filename);
    string line;
    
    if (!file.is_open()) return false;
    
    getline(file, line);
    while (getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() > 0) {
            if (tokens[0] == username) {
                if (!tokens.empty() && tokens.back() == passwordHash) { file.close(); return true; }
            }
        }
    }
    file.close();
    return false;
}

// Updates password hash for user in admin/student file
void FileHandler::updatePassword(const string& username, const string& newPasswordHash, bool isAdmin) {
    string filename = isAdmin ? adminFile : studentFile;
    vector<string> lines;
    ifstream file(filename);
    string line;
    
    if (!file.is_open()) return;
    
    getline(file, line);
    lines.push_back(line);
    
    while (getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() > 0 && tokens[0] == username) {
            if (!tokens.empty()) tokens.back() = newPasswordHash;
            string newLine;
            for (size_t i = 0; i < tokens.size(); ++i) {
                newLine += tokens[i];
                if (i < tokens.size() - 1) newLine += ",";
            }
            lines.push_back(newLine);
        } else {
            lines.push_back(line);
        }
    }
    file.close();
    
    ofstream outFile(filename);
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();
}

// Checks if worker credentials are valid
bool FileHandler::checkWorkerCredentials(const string& workerID, const string& passwordHash) {
    ifstream file(workerFile);
    string line;
    if (!file.is_open()) return false;
    getline(file, line); // skip header
    while (getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 6 && tokens[0] == workerID && tokens[5] == passwordHash) {
            file.close();
            return true;
        }
    }
    file.close();
    return false;
}

// Updates worker password hash in CSV file
void FileHandler::updateWorkerPassword(const string& workerID, const string& newPasswordHash) {
    vector<string> lines;
    ifstream file(workerFile);
    string line;
    if (!file.is_open()) return;
    getline(file, line);
    lines.push_back(line);
    while (getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 6 && tokens[0] == workerID) {
            tokens[5] = newPasswordHash;
        } else if (tokens.size() == 5 && tokens[0] == workerID) {
            tokens.push_back(newPasswordHash);
        }
        string newLine;
        for (size_t i = 0; i < tokens.size(); ++i) {
            newLine += tokens[i];
            if (i < tokens.size() - 1) newLine += ",";
        }
        lines.push_back(newLine);
    }
    file.close();
    ofstream outFile(workerFile);
    for (const auto& l : lines) outFile << l << "\n";
    outFile.close();
}

// Updates worker contact number in CSV file
void FileHandler::updateWorkerContact(const string& workerID, const string& newContact) {
    vector<string> lines;
    ifstream file(workerFile);
    string line;
    if (!file.is_open()) return;
    getline(file, line);
    lines.push_back(line);
    while (getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 5 && tokens[0] == workerID) {
            tokens[4] = newContact;
        }
        string newLine;
        for (size_t i = 0; i < tokens.size(); ++i) {
            newLine += tokens[i];
            if (i < tokens.size() - 1) newLine += ",";
        }
        lines.push_back(newLine);
    }
    file.close();
    ofstream outFile(workerFile);
    for (const auto& l : lines) outFile << l << "\n";
    outFile.close();
}
