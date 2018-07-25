#include "fika/string.hpp"

using namespace fika;

String::String(const char *c_string) {
    const char *iterate = c_string;
    while('\0' != iterate[0]) {
        iterate++;
    }
    const int length = iterate - c_string;

    this->resource = new ImmutableArrayResource<U32>(1, length);

    for (int i = 0; i < length; i++) {
        this->resource->data[i] = c_string[i];
    }
}

const class String String::to_string() const {
    return *this;
}

const Hash String::to_hash() const {
    Hash hash = 0;
    for(U64 i = 0; i < this->resource->array_size; i++) {
        auto d = this->resource->data[i];
        hash = d + (hash << 6) + (hash<< 16) - hash;
    }
    return hash;
}