#pragma once
#ifndef FIKA_OBJECTS_COMPARABLE_OBJECT_HPP
#define FIKA_OBJECTS_COMPARABLE_OBJECT_HPP

#include "types.hpp"

namespace fika {
    class ComparableObject {
    public:
        virtual bool compare(ComparableObject *co) = 0;
    };

    bool compare(U64 a, U64 b);
    bool compare(ComparableObject *a, ComparableObject *b);
}

#endif