#pragma once
#ifndef FIKA_CONTAINERS_ASSOCIATVIE_ARRAY_HPP
#define FIKA_CONTAINERS_ASSOCIATVIE_ARRAY_HPP

namespace fika {
    template<typename K, typename V> class AssociativeArray {
    public:
        virtual V get(K key) = 0;
    };
}

#endif