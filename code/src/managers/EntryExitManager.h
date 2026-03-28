#ifndef ENTRYEXITMANAGER_H
#define ENTRYEXITMANAGER_H
using namespace std;
#include <vector>
#include "../models/EntryExitRecord.h"
#include "../services/FileHandler.h"

class EntryExitManager {
private:
    FileHandler* fileHandler;
    vector<EntryExitRecord> logs;
    int nextRecordID;
    
public:
    // Constructor: initialize with file handler and load existing entry/exit logs
    EntryExitManager(FileHandler* fh);

    // Record student entry, persist log and update dataset
    void logEntry(const string& studentID);

    // Record student exit, persist log and update dataset
    void logExit(const string& studentID);

    // Return logged entries (for admin view/search)
    vector<EntryExitRecord>& getLogs() { 
        return logs; 
    }

    // Load existing logs from CSV into memory
    void loadLogs();

    // Get current status for a student (true if last event is Entry) : returns {isLoggedIn, lastTimestamp}
    pair<bool, string> getCurrentStatus(const string& studentID);
};

#endif