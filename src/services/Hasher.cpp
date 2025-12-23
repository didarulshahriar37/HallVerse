#include "Hasher.h"
#include <functional>

using namespace std;

string Hasher::hash(const string& input) {
    hash<string> hasher;
    return to_string(hasher(input));
}
