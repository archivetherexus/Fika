#pragma once
#ifndef FIKA_MAP_HPP
#define FIKA_MAP_HPP

#include "mutable_associative_array.hpp"
#include "iterator.hpp"

namespace fika {
    template<class K, typename V> class MapIteratorState : public IteratorState<Pair<K, V>> {
    public:
        
        MapIteratorState() {}
        virtual IteratorState<Pair<K, V>> *copy() const override {
            return new MapIteratorState<K, V>(); 
        }
    };

    template<typename K, typename V> class MapResource : public ContainerResource<Pair<K, V>> {
    public:
        MapResource() {

        }
        virtual Pair<K, V> next(IteratorState<Pair<K, V>> *state) {
            return Pair<K, V>(0, 0); // TODO: Implement later on...
        };
        virtual bool has_next(IteratorState<Pair<K, V>> *state) {
            return false; // TODO: Implement later on...
        };
    };

    template<class K, typename V> class Map : public MutableAssociativeArray<K, V> {
    public:
        Map() {
            resource = new MapResource<K, V>();
            resource->reference_count++;
        }
        ~Map() {
            resource->reference_count--;
            if (0 == resource->reference_count) {
                delete resource;
            }
        }
        virtual Iterator<Pair<K, V>> iterator() const {
            return Iterator<Pair<K, V>>(resource, new MapIteratorState<K, V>());
        };
        virtual U64 count() const {
            return 0;
        };
        virtual void clear() {
            return;
        };
    private:
        MapResource<K, V> *resource;
    };
}

#endif