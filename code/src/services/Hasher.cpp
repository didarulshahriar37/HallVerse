#include "Hasher.h"
#include <string>
#include <sstream>

using namespace std;

// Constructor: Initializes hasher with ID
Hasher::Hasher() : id("HASHER_001") {}

// Custom hash: for each character c in the password,
// add (ASCII value of c * 37) to the running total.
// hash = 0; for each c: hash += ASCII(c) * 37
string Hasher::hash(const string& input) {
    long long hashVal = 0;
    for (unsigned char c : input) {
        hashVal += static_cast<long long>(c) * 37;
    }
    return to_string(hashVal);
}