#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include <string>
#include <vector>
#include "../models/Student.h"

class FileHandler {
private:
    std::string studentFile;
    std::string adminFile;
    std::string complaintFile;
    std::string workerFile;
    std::string assignmentFile;
    std::string entryExitFile;

public:
    FileHandler();

    std::vector<Student> readStudents();
    void writeStudents(const std::vector<Student>& students);
};

#endif
