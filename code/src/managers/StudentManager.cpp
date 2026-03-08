#include "StudentManager.h"
#include <iostream>
 
using namespace std;
StudentManager::StudentManager(FileHandler* fh) : fileHandler(fh) {
    loadStudents();
}

void StudentManager::loadStudents() {
    students = fileHandler->readStudents();
}

void StudentManager::addStudent(const Student& student) {
    students.push_back(student);
    fileHandler->writeStudents(students);
    cout << "Student added successfully!\n";
}

void StudentManager::updateStudent(const Student& student) {
    for (auto& s : students) {
        if (s.getStudentID() == student.getStudentID()) {
            s = student;
            fileHandler->writeStudents(students);
            cout << "Student updated successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

void StudentManager::removeStudent(const string& studentID) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getStudentID() == studentID) {
            students.erase(it);
            fileHandler->writeStudents(students);
            cout << "Student removed successfully!\n";
            return;
        }
    }
    cout << "Student not found!\n";
}

Student* StudentManager::getStudent(const string& studentID) {
    for (auto& s : students) {
        if (s.getStudentID() == studentID) {
            return &s;
        }
    }
    return nullptr;
}

bool StudentManager::isBedOccupied(const string& hall, const string& room, const string& bed) const {
    for (const auto& s : students) {
        if (s.getHallName() == hall && s.getRoomNumber() == room && s.getBedNumber() == bed) return true;
    }
    return false;
}

void StudentManager::resetAllPasswords(const string& defaultHash) {
    for (auto& s : students) {
        s.setPasswordHash(defaultHash);
    }
    fileHandler->writeStudents(students);
    cout << "All student passwords have been reset to default.\n";
}

void StudentManager::saveAll() {
    fileHandler->writeStudents(students);
}