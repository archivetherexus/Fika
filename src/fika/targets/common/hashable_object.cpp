#include "fika/objects/hashable_object.hpp"

using namespace fika;

Hash ToHashFunctions::to_hash(I64 arg) {
    arg = (arg ^ (arg >> 30)) * 0xbf58476d1ce4e5b9ULL;
    arg = (arg ^ (arg >> 27)) * 0x94d049bb133111ebULL;
    arg = arg ^ (arg >> 31);
    return arg;
}
Hash ToHashFunctions::to_hash(I32 arg) {
    arg = ((arg >> 16) ^ arg) * 0x45d9f3b;
    arg = ((arg >> 16) ^ arg) * 0x45d9f3b;
    arg = (arg >> 16) ^ arg;
    return arg;
}
Hash ToHashFunctions::to_hash(U64 arg) {
    arg = (arg ^ (arg >> 30)) * 0xbf58476d1ce4e5b9ULL;
    arg = (arg ^ (arg >> 27)) * 0x94d049bb133111ebULL;
    arg = arg ^ (arg >> 31);
    return arg;
}
Hash ToHashFunctions::to_hash(U32 arg) {
    arg = ((arg >> 16) ^ arg) * 0x45d9f3b;
    arg = ((arg >> 16) ^ arg) * 0x45d9f3b;
    arg = (arg >> 16) ^ arg;
    return arg;
}
Hash ToHashFunctions::to_hash(HashableObject *arg) {
    return arg->to_hash();
}
Hash ToHashFunctions::to_hash(HashableObject &arg) {
    return arg.to_hash();
}