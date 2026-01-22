#ifndef WORKER_H
#define WORKER_H

#include <string>

class Worker {
private:
    std::string workerID;
    std::string name;
    std::string role;
    bool isAvailable;
    std::string contactNumber;
    
public:
    Worker();
    Worker(std::string id, std::string n, std::string r, bool avail, std::string contact);
    
    void markAvailable();
    void markUnavailable();
    bool checkAvailability() const;
    
    std::string getWorkerID() const { return workerID; }
    std::string getName() const { return name; }
    std::string getRole() const { return role; }
    bool getIsAvailable() const { return isAvailable; }
    std::string getContactNumber() const { return contactNumber; }
};

#endif