#ifndef HASHER_H
#define HASHER_H

#include <string>
using namespace std;
class Hasher {
private:
    string id;
public:
    Hasher();
    string hash(const std::string& input);
};

#endif