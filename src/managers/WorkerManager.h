#ifndef WORKER_MANAGER_H
#define WORKER_MANAGER_H
using namespace std;
#include <vector>
#include "../models/Worker.h"
#include "../services/FileHandler.h"




class WorkerManager {
private:
    FileHandler* fileHandler;
    vector<Worker> workers;

public:
    WorkerManager(FileHandler* fh);

    void loadWorkers();

    Worker* findAvailableWorker(const string& role);
    void updateWorkerStatus(const string& workerID, bool availability);
    vector<Worker>& getAllWorkers() { return workers; }
};

#endif
