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
    EntryExitManager(FileHandler* fh);
    void logEntry(const string& studentID);
    void logExit(const string& studentID);
    vector<EntryExitRecord>& getLogs() { return logs; }
    void loadLogs();
    pair<bool, string> getCurrentStatus(const string& studentID); // returns {isLoggedIn, lastTimestamp}
};

#endif