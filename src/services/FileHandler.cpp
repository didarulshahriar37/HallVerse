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
FileHandler::FileHandler() 
    : id("FH_001"),
      studentFile("data/students.csv"),
      adminFile("data/admins.csv"),
      complaintFile("data/complaints.csv"),
      workerFile("data/workers.csv"),
      assignmentFile("data/assignments.csv"),
      entryExitFile("data/entry_exit.csv") {}

std::vector<std::string> FileHandler::split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<Student> FileHandler::readStudents() {
    std::vector<Student> students;
    std::ifstream file(studentFile);
    std::string line;
    
    if (!file.is_open()) return students;

    std::getline(file, line);
    while (std::getline(file, line)) {
        try {
            auto tokens = split(line, ',');
            // Possible formats (columns):
            // 9: id,name,email,emergencyContact,roomNumber,bedNumber,hallName,hallDues,password
            // 8: id,name,email,emergencyContact,roomNumber,bedNumber,hallDues,password
            // 7: legacy id,name,email,emergencyContact,roomNumber,hallDues,password
            if (tokens.size() >= 9) {
                double dues = 0.0;
                try { dues = std::stod(tokens[7]); } catch (...) { dues = 0.0; }
                students.push_back(Student(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], tokens[6], dues));
            } else if (tokens.size() == 8) {
                double dues = 0.0;
                try { dues = std::stod(tokens[6]); } catch (...) { dues = 0.0; }
                students.push_back(Student(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], tokens[5], std::string(""), dues));
            } else if (tokens.size() >= 7) {
                double dues = 0.0;
                try { dues = std::stod(tokens[5]); } catch (...) { dues = 0.0; }
                students.push_back(Student(tokens[0], tokens[1], tokens[2], tokens[3], tokens[4], std::string(""), std::string(""), dues));
            }
        } catch (const std::exception& e) {
            std::cerr << "Error parsing student line: " << e.what() << std::endl;
        }
    }
    file.close();
    return students;
}

void FileHandler::writeStudents(const std::vector<Student>& students) {
    std::ofstream file(studentFile);
    file << "studentID,name,email,emergencyContact,roomNumber,bedNumber,hallName,hallDues,password\n";
    for (const auto& s : students) {
        file << s.getStudentID() << "," << s.getName() << "," << s.getEmail() << ","
             << s.getEmergencyContact() << "," << s.getRoomNumber() << ","
             << s.getBedNumber() << "," << s.getHallName() << "," << s.getHallDues() << ",5e884898da28047151d0e56f8dc6292773603d0d6aabbdd62a11ef721d1542d8\n";
    }
    file.close();
}

std::vector<Complaint> FileHandler::readComplaints() {
    std::vector<Complaint> complaints;
    std::ifstream file(complaintFile);
    std::string line;
    
    if (!file.is_open()) return complaints;
    
    std::getline(file, line);
    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 6) {
            complaints.push_back(Complaint(tokens[0], tokens[1], tokens[2], 
                                         tokens[3], tokens[4], tokens[5]));
        }
    }
    file.close();
    return complaints;
}

void FileHandler::writeComplaints(const std::vector<Complaint>& complaints) {
    std::ofstream file(complaintFile);
    file << "complaintID,studentID,category,description,status,date\n";
    for (const auto& c : complaints) {
        file << c.getComplaintID() << "," << c.getStudentID() << "," 
             << c.getCategory() << "," << c.getDescription() << "," 
             << c.getStatus() << "," << c.getDate() << "\n";
    }
    file.close();
}

std::vector<Worker> FileHandler::readWorkers() {
    std::vector<Worker> workers;
    std::ifstream file(workerFile);
    std::string line;
    
    if (!file.is_open()) return workers;
    
    std::getline(file, line);
    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 5) {
            // Handle different representations of availability: "1", "true", "0", "false"
            bool avail = (tokens[3] == "1" || tokens[3] == "true" || tokens[3] == "True");
            workers.push_back(Worker(tokens[0], tokens[1], tokens[2], avail, tokens[4]));
        }
    }
    file.close();
    return workers;
}

void FileHandler::writeWorkers(const std::vector<Worker>& workers) {
    std::ofstream file(workerFile);
    file << "workerID,name,role,isAvailable,contactNumber\n";
    for (const auto& w : workers) {
        file << w.getWorkerID() << "," << w.getName() << "," << w.getRole() << ","
             << w.getIsAvailable() << "," << w.getContactNumber() << "\n";
    }
    file.close();
}

std::vector<WorkAssignment> FileHandler::readAssignments() {
    std::vector<WorkAssignment> assignments;
    std::ifstream file(assignmentFile);
    std::string line;
    
    if (!file.is_open()) return assignments;
    
    std::getline(file, line);
    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 5) {
            assignments.push_back(WorkAssignment(tokens[0], tokens[1], tokens[2], 
                                                tokens[3], tokens[4]));
        }
    }
    file.close();
    return assignments;
}

void FileHandler::writeAssignments(const std::vector<WorkAssignment>& assignments) {
    std::ofstream file(assignmentFile);
    file << "assignmentID,complaintID,workerID,status,report\n";
    for (const auto& a : assignments) {
        file << a.getAssignmentID() << "," << a.getComplaintID() << "," 
             << a.getWorkerID() << "," << a.getStatus() << "," 
             << a.getReport() << "\n";
    }
    file.close();
}

std::vector<EntryExitRecord> FileHandler::readEntryExitLogs() {
    std::vector<EntryExitRecord> records;
    std::ifstream file(entryExitFile);
    std::string line;
    
    if (!file.is_open()) return records;
    
    std::getline(file, line);
    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() >= 4) {
            records.push_back(EntryExitRecord(tokens[0], tokens[1], tokens[2], tokens[3]));
        }
    }
    file.close();
    return records;
}

void FileHandler::writeEntryExitLogs(const std::vector<EntryExitRecord>& records) {
    std::ofstream file(entryExitFile);
    file << "recordID,studentID,type,timestamp\n";
    for (const auto& r : records) {
        file << r.getRecordID() << "," << r.getStudentID() << "," 
             << r.getType() << "," << r.getTimestamp() << "\n";
    }
    file.close();
}

bool FileHandler::checkCredentials(const std::string& username, const std::string& passwordHash, bool isAdmin) {
    std::string filename = isAdmin ? adminFile : studentFile;
    std::ifstream file(filename);
    std::string line;
    
    if (!file.is_open()) return false;
    
    std::getline(file, line);
    while (std::getline(file, line)) {
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

void FileHandler::updatePassword(const std::string& username, const std::string& newPasswordHash, bool isAdmin) {
    std::string filename = isAdmin ? adminFile : studentFile;
    std::vector<std::string> lines;
    std::ifstream file(filename);
    std::string line;
    
    if (!file.is_open()) return;
    
    std::getline(file, line);
    lines.push_back(line);
    
    while (std::getline(file, line)) {
        auto tokens = split(line, ',');
        if (tokens.size() > 0 && tokens[0] == username) {
            if (!tokens.empty()) tokens.back() = newPasswordHash;
            std::string newLine;
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
    
    std::ofstream outFile(filename);
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();
}