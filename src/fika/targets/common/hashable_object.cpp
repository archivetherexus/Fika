#include "fika/objects/hashable_object.hpp"

using namespace fika;

Hash ToHashFunctions::to_hash(I64 arg) {
    return 0; // TODO: We need a proper int hash here...
}
Hash ToHashFunctions::to_hash(I32 arg) {
    return 0; // TODO: We need a proper int hash here...
}
Hash ToHashFunctions::to_hash(U64 arg) {
    return 0; // TODO: We need a proper int hash here...
}
Hash ToHashFunctions::to_hash(U32 arg) {
    return 0; // TODO: We need a proper int hash here...
}
Hash ToHashFunctions::to_hash(HashableObject *arg) {
    return arg->to_hash();
}
Hash ToHashFunctions::to_hash(HashableObject &arg) {
    return arg.to_hash();
}