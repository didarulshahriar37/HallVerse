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
    
    // Helper function: Splits a string by delimiter for CSV parsing
    // Features used: CSV file parsing, data import
    vector<string> split(const string& str, char delimiter);
    
public:
    // Constructor: Initializes file paths for all data files
    // Features used: File system management, data persistence setup
    FileHandler();
    
    // Reads student data from CSV file and returns vector of Student objects
    // Features used: Student data loading, CSV parsing, data import
    vector<Student> readStudents();
    
    // Writes student data to CSV file with header
    // Features used: Student data persistence, CSV export, data backup
    void writeStudents(const vector<Student>& students);
    
    // Reads complaint data from CSV file and returns vector of Complaint objects
    // Features used: Complaint data loading, issue tracking import
    vector<Complaint> readComplaints();
    
    // Writes complaint data to CSV file
    // Features used: Complaint data persistence, issue tracking export
    void writeComplaints(const vector<Complaint>& complaints);
    
    // Reads worker data from CSV file and returns vector of Worker objects
    // Features used: Worker data loading, staff management import
    vector<Worker> readWorkers();
    
    // Writes worker data to CSV file
    // Features used: Worker data persistence, staff management export
    void writeWorkers(const vector<Worker>& workers);
    
    // Reads work assignment data from CSV file
    // Features used: Assignment data loading, task management import
    vector<WorkAssignment> readAssignments();
    
    // Writes work assignment data to CSV file
    // Features used: Assignment data persistence, task management export
    void writeAssignments(const vector<WorkAssignment>& assignments);
    
    // Reads entry/exit log data from CSV file
    // Features used: Log data loading, access tracking import
    vector<EntryExitRecord> readEntryExitLogs();
    
    // Writes entry/exit log data to CSV file
    // Features used: Log data persistence, access tracking export
    void writeEntryExitLogs(const vector<EntryExitRecord>& records);
    
    // Checks if username/password hash combination exists in admin or student file
    // Features used: Authentication verification, login system
    bool checkCredentials(const string& username, const string& passwordHash, bool isAdmin);
    
    // Updates password hash for user in admin/student file
    // Features used: Password reset, credential management
    void updatePassword(const string& username, const string& newPasswordHash, bool isAdmin);

    // Checks if worker credentials are valid
    // Features used: Worker authentication, staff login system
    bool checkWorkerCredentials(const string& workerID, const string& passwordHash);
    
    // Updates worker password hash in CSV file
    // Features used: Worker password reset, staff credential management
    void updateWorkerPassword(const string& workerID, const string& newPasswordHash);
    
    // Updates worker contact number in CSV file
    // Features used: Worker contact management, staff information updates
    void updateWorkerContact(const string& workerID, const string& newContact);
};

#endif