#include "Hasher.h"
#include <functional>

using namespace std;

string Hasher::hash(const string& input) {
    std::hash<string> hasher;
    return to_string(hasher(input));
}
