#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
using namespace std;
class Student;
class Complaint;
class Worker;
class WorkAssignment;
class EntryExitRecord;

class FileHandler {
private:
    string id;
    string studentFile;
    string adminFile;
    string complaintFile;
    string workerFile;
    string assignmentFile;
    string entryExitFile;
    
    vector<string> split(const string& str, char delimiter);
    
public:
    FileHandler();
    
    vector<Student> readStudents();
    void writeStudents(const vector<Student>& students);
    
    vector<Complaint> readComplaints();
    void writeComplaints(const vector<Complaint>& complaints);
    
    vector<Worker> readWorkers();
    void writeWorkers(const vector<Worker>& workers);
    
    vector<WorkAssignment> readAssignments();
    void writeAssignments(const vector<WorkAssignment>& assignments);
    
    vector<EntryExitRecord> readEntryExitLogs();
    void writeEntryExitLogs(const vector<EntryExitRecord>& records);
    
    bool checkCredentials(const string& username, const string& passwordHash, bool isAdmin);
    void updatePassword(const string& username, const string& newPasswordHash, bool isAdmin);

    bool checkWorkerCredentials(const string& workerID, const string& passwordHash);
    void updateWorkerPassword(const string& workerID, const string& newPasswordHash);
    void updateWorkerContact(const string& workerID, const string& newContact);
};

#endif