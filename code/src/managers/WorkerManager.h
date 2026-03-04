#ifndef WORKER_MANAGER_H
#define WORKER_MANAGER_H
using namespace std;
#include <vector>
#include "../models/Worker.h"
#include "../services/FileHandler.h"
#include "../services/Hasher.h"




class WorkerManager {
private:
    FileHandler* fileHandler;
    Hasher* hasher;
    vector<Worker> workers;

public:
    WorkerManager(FileHandler* fh, Hasher* h);

    void loadWorkers();
    void saveWorkers();

    bool loginWorker(const string& workerID, const string& password);

    Worker* findAvailableWorker(const string& role);
    Worker* findLeastLoadedWorker(const string& role);
    Worker* findWorkerByID(const string& workerID);
    void updateWorkerStatus(const string& workerID, bool availability);
    void updateContactNumber(const string& workerID, const string& newContact);
    vector<Worker>& getAllWorkers() { return workers; }
};

#endif
