#ifndef HASHER_H
#define HASHER_H

#include <string>

class Hasher {
private:
    std::string id;
public:
    Hasher();
    std::string hash(const std::string& input);
};

#endif