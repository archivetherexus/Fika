#include "fika/string.hpp"

using namespace fika;

String::String(const char *c_string) {
    const char *iterate = c_string;
    while('\0' != iterate[0]) {
        iterate++;
    }
    const int length = iterate - c_string;

    this->resource = new ImmutableArrayResource<U32>(length);
    this->resource->reference_count++;

    for (int i = 0; i < length; i++) {
        this->resource->data[i] = c_string[i];
    }
}

const String String::to_string() const {
    return *this;
}

