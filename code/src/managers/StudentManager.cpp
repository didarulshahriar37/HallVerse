#include "StudentManager.h"
#include <iostream>
 
using namespace std;

// StudentManager coordinates student CRUD operations and persistence.
// It keeps student vector in-memory and writes through FileHandler.
StudentManager::StudentManager(FileHandler* fh) : fileHandler(fh) {
    loadStudents();
}

// Loads students from CSV file into memory
void StudentManager::loadStudents() {
    students = fileHandler->readStudents();
}

// Adds new student to memory and persists to file
void StudentManager::addStudent(const Student& student) {
    students.push_back(student);
    fileHandler->writeStudents(students);
    cout << "Student added successfully!\n";
}

// Updates existing student record in file
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

// Removes student by ID and persists change
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

// Retrieves pointer to student by ID (returns nullptr if not found)
Student* StudentManager::getStudent(const string& studentID) {
    for (auto& s : students) {
        if (s.getStudentID() == studentID) {
            return &s;
        }
    }
    return nullptr;
}

// Checks if bed is already assigned to another student
bool StudentManager::isBedOccupied(const string& hall, const string& room, const string& bed) const {
    for (const auto& s : students) {
        if (s.getHallName() == hall && s.getRoomNumber() == room && s.getBedNumber() == bed) return true;
    }
    return false;
}

// Sets all students to same password hash (for admin reset)
void StudentManager::resetAllPasswords(const string& defaultHash) {
    for (auto& s : students) {
        s.setPasswordHash(defaultHash);
    }
    fileHandler->writeStudents(students);
    cout << "All student passwords have been reset to default.\n";
}

// Persists all student data to file
void StudentManager::saveAll() {
    fileHandler->writeStudents(students);
}