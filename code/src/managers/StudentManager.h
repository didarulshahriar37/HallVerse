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
    // Constructor: Inject file handler dependency and load existing student data
    StudentManager(FileHandler* fh);

    // Load all students from data/students.csv into memory
    void loadStudents();

    // Add one student and persist update
    void addStudent(const Student& student);

    // Update one student by ID and persist
    void updateStudent(const Student& student);

    // Remove one student by ID and persist
    void removeStudent(const string& studentID);

    // Lookup student by ID (returns pointer or nullptr if missing)
    Student* getStudent(const string& studentID);

    // Check if bed is currently assigned to a student
    bool isBedOccupied(const string& hall, const string& room, const string& bed) const;

    // Return all students in memory reference for read/write loops
    vector<Student>& getAllStudents() {
         return students; 
    }

    // Reset every student password hash to the provided default (e.g. hashed "password")
    void resetAllPasswords(const string& defaultHash);

    // Persist current in-memory student list to disk
    void saveAll();
};

#endif