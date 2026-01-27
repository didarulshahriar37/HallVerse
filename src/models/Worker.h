#ifndef WORKER_H
#define WORKER_H

#include <string>
using namespace std;
class Worker {
private:
    string workerID;
    string name;
    string role;
    bool isAvailable;
    string contactNumber;
    
public:
    Worker();
    Worker(string id, string n, string r, bool avail, string contact);
    
    void markAvailable();
    void markUnavailable();
    bool checkAvailability() const;
    
    string getWorkerID() const { return workerID; }
    string getName() const { return name; }
    string getRole() const { return role; }
    bool getIsAvailable() const { return isAvailable; }
    string getContactNumber() const { return contactNumber; }
};

#endif