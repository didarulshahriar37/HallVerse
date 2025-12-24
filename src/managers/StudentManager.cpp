#include "StudentManager.h"
#include "../models/Student.h"
#include "../services/FileHandler.h"

using namespace std;

StudentManager::StudentManager(FileHandler* fileHandler) {
    this->fileHandler = fileHandler;
    loadStudents();
}

void StudentManager::loadStudents() {
    students = fileHandler->readStudents();
}

void StudentManager::addStudent(const Student& student) {
    students.push_back(student);
    fileHandler->writeStudents(students);
}

void StudentManager::updateStudent(const Student& updatedStudent) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getStudentID() == updatedStudent.getStudentID()) {
            students[i] = updatedStudent;
            fileHandler->writeStudents(students);
            return;
        }
    }
}

void StudentManager::removeStudent(const string& studentID) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getStudentID() == studentID) {
            students.erase(students.begin() + i);
            fileHandler->writeStudents(students);
            return;
        }
    }
}

Student* StudentManager::getStudent(const string& studentID) {
    for (size_t i = 0; i < students.size(); i++) {
        if (students[i].getStudentID() == studentID) {
            return &students[i];
        }
    }
    return nullptr;
}
