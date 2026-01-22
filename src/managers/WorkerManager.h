#ifndef WORKER_MANAGER_H
#define WORKER_MANAGER_H

#include <vector>
#include "../models/Worker.h"
#include "../services/FileHandler.h"




class WorkerManager {
private:
    FileHandler* fileHandler;
    std::vector<Worker> workers;

public:
    WorkerManager(FileHandler* fh);

    void loadWorkers();

    Worker* findAvailableWorker(const std::string& role);
    void updateWorkerStatus(const std::string& workerID, bool availability);
    std::vector<Worker>& getAllWorkers() { return workers; }
};

#endif
