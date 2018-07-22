#pragma once
#ifndef ASSOCIATVIE_ARRAY_HPP
#define ASSOCIATVIE_ARRAY_HPP

namespace fika {
    template<typename K, typename V> class AssociativeArray {
    public:
        virtual V get(K key) = 0;
    };
}

#endif