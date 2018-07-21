#pragma once
#ifndef FIKA_IMMUTABLE_ASSOCIATIVE_ARRAY_HPP
#define FIKA_IMMUTABLE_ASSOCIATIVE_ARRAY_HPP

#include "associative_array.hpp"
#include "pair.hpp"
#include "container.hpp"

namespace fika {
    template<typename K, typename V> class ImmutableAssociativeArray : public AssociativeArray<K, V>, public Container<Pair<K, V>> {

    };
}

#endif