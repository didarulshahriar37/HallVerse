#ifndef WORKER_MANAGER_H
#define WORKER_MANAGER_H

#include <vector>
#include "../models/Worker.h"
#include "../services/FileHandler.h"


class Worker;
class FileHandler;

class WorkerManager {
private:
    FileHandler* fileHandler;
    std::vector<Worker> workers;

public:
    WorkerManager(FileHandler* fileHandler);

    void loadWorkers();

    void addWorker(const Worker& worker);
    void updateWorkerStatus(const std::string& workerID, const std::string& newStatus);

    std::vector<Worker> getAllWorkers();
    Worker* getAvailableWorkerByRole(const std::string& role);
};

#endif
