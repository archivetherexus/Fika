#include "fika/objects/comparable_object.hpp"

using namespace fika;

bool fika::compare(U64 a, U64 b) {
    return a == b;
} 
bool fika::compare(ComparableObject *a, ComparableObject *b) {
    a->compare(b);
}