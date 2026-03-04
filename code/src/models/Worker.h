#ifndef WORKER_H
#define WORKER_H

#include <string>
#include <vector>

using namespace std;

class Worker
{
private:
    string workerID;
    string name;
    string role;
    string contactNumber;
    bool isAvailable;
    string passwordHash;

    int activeComplaints;
    int resolvedComplaints;
    vector<string> assignedComplaintIDs;

public:
    // constructors
    Worker();
    Worker(const string &id,
           const string &n,
           const string &r,
           bool avail,
           const string &contact,
           const string &pwdHash = "");

    // availability control
    void markAvailable();
    void markUnavailable();
    bool checkAvailability() const;

    // complaint workflow
    void assignComplaint(const string &complaintID);
    void completeComplaint(const string &complaintID);
    void updateComplaintStatus(const string &complaintID, const string &status);

    // getters
    string getWorkerID() const;
    string getName() const;
    string getRole() const;
    string getContactNumber() const;
    bool getIsAvailable() const;
    int getActiveComplaints() const;
    int getResolvedComplaints() const;
    vector<string> getAssignedComplaints() const;
    string getPasswordHash() const;
    void setPasswordHash(const string& hash);
    void setContactNumber(const string& contact);
};

#endif