#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H
using namespace std;
#include <vector>
#include "../models/Student.h"
#include "../services/FileHandler.h"

class StudentManager {
private:
    FileHandler* fileHandler;
    vector<Student> students;

public:
    StudentManager(FileHandler* fh);
    void loadStudents();
    void addStudent(const Student& student);
    void updateStudent(const Student& student);
    void removeStudent(const string& studentID);
    Student* getStudent(const string& studentID);
    bool isBedOccupied(const string& hall, const string& room, const string& bed) const;
    vector<Student>& getAllStudents() { return students; }

    // Reset every student password hash to the provided default (e.g. hashed "password")
    void resetAllPasswords(const string& defaultHash);

    void saveAll();
};

#endif