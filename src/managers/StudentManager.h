#ifndef STUDENT_MANAGER_H
#define STUDENT_MANAGER_H

#include <vector>
#include <string>

class Student;
class FileHandler;

class StudentManager {
private:
    FileHandler* fileHandler;
    std::vector<Student> students;

public:
    StudentManager(FileHandler* fileHandler);

    void loadStudents();
    void addStudent(const Student& student);
    void updateStudent(const Student& student);
    void removeStudent(const std::string& studentID);
    Student* getStudent(const std::string& studentID);
};

#endif
