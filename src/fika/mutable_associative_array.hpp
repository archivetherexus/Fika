#pragma once
#ifndef FIKA_MUTABLE_ASSOCIATIVE_ARRAY_HPP
#define FIKA_MUTABLE_ASSOCIATIVE_ARRAY_HPP

#include "associative_array.hpp"
#include "pair.hpp"
#include "mutable_container.hpp"

namespace fika {
    template<typename K, typename V> class MutableAssociativeArray : public AssociativeArray<K, V>, public MutableContainer<Pair<K, V>> {
    public:

    };
}

#endif