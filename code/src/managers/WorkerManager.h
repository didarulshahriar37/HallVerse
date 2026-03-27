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
    // Constructor: set FileHandler and Hasher dependencies, then load existing workers
    WorkerManager(FileHandler* fh, Hasher* h);

    // Load workers from persistence into memory
    void loadWorkers();

    // Save workers snapshot to file
    void saveWorkers();

    // Worker login: verify password against stored hash
    bool loginWorker(const string& workerID, const string& password);

    // Find any available worker for given role
    Worker* findAvailableWorker(const string& role);

    // Find worker with smallest active task count for load balancing
    Worker* findLeastLoadedWorker(const string& role);

    // Find worker by ID
    Worker* findWorkerByID(const string& workerID);

    // Change worker availability status and persist
    void updateWorkerStatus(const string& workerID, bool availability);

    // Update worker contact number and persist
    void updateContactNumber(const string& workerID, const string& newContact);

    // Change worker password (hashed) and persist
    void updateWorkerPassword(const string& workerID, const string& newPassword);

    // Verify worker password by comparing hash
    bool verifyWorkerPassword(const string& workerID, const string& password);

    // Access all workers in memory
    vector<Worker>& getAllWorkers() { return workers; }
};

#endif
