#ifndef ENTRYEXITRECORD_H
#define ENTRYEXITRECORD_H

#include<string>
using namespace std;

class EntryExitRecord{

    private:
    string recordID;
    string studentID;
    string type;
    string timestamp;

    public:
    void displayRecord();
};

#endif