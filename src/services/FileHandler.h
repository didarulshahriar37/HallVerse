#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>

using namespace std;

class FileHandler {
private:
    string studentFile;
    string adminFile;
    string complaintFile;
    string workerFile;
    string assignmentFile;
    string entryExitFile;

public:
    FileHandler();

    vector<string> readStudents();
    void writeStudents(const vector<string>& data);

    vector<string> readAdmins();

    vector<string> readComplaints();
    void writeComplaints(const vector<string>& data);

    vector<string> readWorkers();
    void writeWorkers(const vector<string>& data);

    vector<string> readAssignments();
    void writeAssignments(const vector<string>& data);

    vector<string> readEntryExitLogs();
    void writeEntryExitLogs(const vector<string>& data);
};

#endif
