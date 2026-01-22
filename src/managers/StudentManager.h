#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include <vector>
#include "../models/Student.h"
#include "../services/FileHandler.h"

class StudentManager {
private:
    FileHandler* fileHandler;
    std::vector<Student> students;

public:
    StudentManager(FileHandler* fh);
    void loadStudents();
    void addStudent(const Student& student);
    void updateStudent(const Student& student);
    void removeStudent(const std::string& studentID);
    Student* getStudent(const std::string& studentID);
    bool isBedOccupied(const std::string& hall, const std::string& room, const std::string& bed) const;
    std::vector<Student>& getAllStudents() { return students; }
};

#endif