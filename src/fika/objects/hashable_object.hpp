#pragma once
#ifndef FIKA_HASHABLE_OBJECT_HPP
#define FIKA_HASHABLE_OBJECT_HPP

#include "types.hpp"

namespace fika {
    typedef U64 Hash;
    class HashableObject {
    public:
        virtual const Hash to_hash() const = 0;
    };
    class ToHashFunctions {
    public:
        ToHashFunctions() = delete;
        static Hash to_hash(I32 arg);
        static Hash to_hash(I64 arg);
        static Hash to_hash(U32 arg);
        static Hash to_hash(U64 arg);
        static Hash to_hash(HashableObject *arg);
        static Hash to_hash(HashableObject &arg);
    };
    template<typename A> Hash to_hash(A *arg) {
        return ToHashFunctions::to_hash(&arg);
    }
    template<typename A> Hash to_hash(A arg) {
        return ToHashFunctions::to_hash(arg);
    }
}

#endif