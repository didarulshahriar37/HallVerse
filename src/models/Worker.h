#ifndef WORKER_H
#define WORKER_H

#include<string>
using namespace std;

class Worker{
    
    private:
    string workerID;
    string name;
    string role;
    bool isAvailable;
    string contactNumber;

    public:
    void markAvailable();
    void markUnavailable();
    bool checkAvailability();
};

#endif