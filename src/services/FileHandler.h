#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>

class Student;
class Complaint;
class Worker;
class WorkAssignment;
class EntryExitRecord;

class FileHandler {
private:
    std::string id;
    std::string studentFile;
    std::string adminFile;
    std::string complaintFile;
    std::string workerFile;
    std::string assignmentFile;
    std::string entryExitFile;
    
    std::vector<std::string> split(const std::string& str, char delimiter);
    
public:
    FileHandler();
    
    std::vector<Student> readStudents();
    void writeStudents(const std::vector<Student>& students);
    
    std::vector<Complaint> readComplaints();
    void writeComplaints(const std::vector<Complaint>& complaints);
    
    std::vector<Worker> readWorkers();
    void writeWorkers(const std::vector<Worker>& workers);
    
    std::vector<WorkAssignment> readAssignments();
    void writeAssignments(const std::vector<WorkAssignment>& assignments);
    
    std::vector<EntryExitRecord> readEntryExitLogs();
    void writeEntryExitLogs(const std::vector<EntryExitRecord>& records);
    
    bool checkCredentials(const std::string& username, const std::string& passwordHash, bool isAdmin);
    void updatePassword(const std::string& username, const std::string& newPasswordHash, bool isAdmin);
};

#endif