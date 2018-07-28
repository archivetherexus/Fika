#pragma once
#ifndef FIKA_MAP_HPP
#define FIKA_MAP_HPP

#include "mutable_associative_array.hpp"
#include "fika/objects/comparable_object.hpp"
#include "fika/iterator.hpp"
#include "fika/pair.hpp"

namespace fika {
    template<class K, typename V> class MapPoolEntry {
    public:
        MapPoolEntry()
        : next(nullptr) {

        }
        MapPoolEntry(K key, V value, MapPoolEntry<K, V> *next)
        : key(key)
        , value(value)
        , next(next) {

        }

        K key;
        V value;
        MapPoolEntry<K, V> *next;
    };
    template<class K, typename V> class MapIteratorState : public IteratorState<Pair<K, V>> {
    public:
        U64 pool_index = 0;
        MapPoolEntry<K, V> *current_entry;
        MapIteratorState(U64 pool_index, MapPoolEntry<K, V> *current_entry)
        : pool_index(pool_index)
        , current_entry(current_entry) {

        }
        virtual IteratorState<Pair<K, V>> *copy() const override {
            return new MapIteratorState<K, V>(pool_index, current_entry); 
        }
    };

    template<class K, typename V> class MapResource : public ContainerResource<Pair<K, V>> {
    public:
        MapPoolEntry<K, V> **pool;
        U64 pool_size;
        U64 elements;
        MapResource(U64 pool_size)
        : ContainerResource<Pair<K, V>>(0)
        , pool_size(pool_size) {
            pool = new MapPoolEntry<K, V>*[pool_size];

            // TODO: Is this really necessary?
            for (U64 i = 0; i < pool_size; i++) {
                pool[i] = nullptr;
            }
        }
        ~MapResource() {
            for (U64 i = 0; i < pool_size; i++) {
                auto *entry = pool[i];
                while (nullptr != entry) {
                    auto next = entry->next;
                    delete entry;
                    entry = next;
                }
            }
            delete[] pool;
        }
        virtual Pair<K, V> next(IteratorState<Pair<K, V>> *uncasted_state, Pair<K, V> *default_value) {
            auto *state = static_cast<MapIteratorState<K, V>*>(uncasted_state);
            while (nullptr == state->current_entry) {
                if (state->pool_index >= pool_size) {
                    return *default_value;
                }
                state->current_entry = pool[state->pool_index];
                state->pool_index++;
            }
            auto *entry = state->current_entry;
            state->current_entry = state->current_entry->next;
            return Pair<K, V>(entry->key, entry->value);
        
        };
        virtual bool has_next(IteratorState<Pair<K, V>> *uncasted_state) {
            auto state = static_cast<MapIteratorState<K, V>*>(uncasted_state);
            U64 i = state->pool_index;
            if (nullptr == state->current_entry) {
                while(i < pool_size && nullptr == pool[i]) {
                    i++;
                }
                return i < pool_size;
            } else {
                return true;
            }
        };
    };

    template<class K, typename V> class Map : public MutableAssociativeArray<K, V> {
    public:
        static Map<K, V> create() {
            return Map<K, V>(new MapResource<K, V>(128));
        }
        static Map<K, V> create(I64 pool_size) {
            if (1 > pool_size) {
                pool_size = 1;
            }
            return Map<K, V>(new MapResource<K, V>((U64)pool_size));
        }
        ~Map() {
            if (0 == --resource->reference_count) {
                delete resource;
            }
        }
        Map(const Map<K, V> &other)
        : Map(other.resource) {

        }
        virtual V get(K key) {
            auto hash = to_hash<K>(key);
            auto *latest_entry = resource->pool[hash % resource->pool_size];
            while(latest_entry != nullptr) {
                if (compare(key, latest_entry->key)) {
                    return latest_entry->value;
                }
                latest_entry = latest_entry->next;
            }

            // TODO: Add default value!
        }
        virtual void set(K key, V value) {
            auto hash = to_hash<K>(key);
            auto **latest_entry = &resource->pool[hash % resource->pool_size];
            *latest_entry = new MapPoolEntry<K, V>(key, value, *latest_entry);
        }
        virtual Iterator<Pair<K, V>> iterator(Pair<K, V> default_value) const {
            return Iterator<Pair<K, V>>(resource, new MapIteratorState<K, V>(0, nullptr), default_value);
        };
        virtual U64 count() const {
            return resource->elements;
        };
        virtual void clear() {
            for(U64 i = 0; i < resource->pool_size; i++) {
                auto *entry = resource->pool[i];
                while (nullptr != entry) {
                    auto next = entry->next;
                    delete entry;
                    entry = next;
                }
                resource->pool[i] = nullptr;
            }
            resource->elements = 0;
        };
        Map &operator = (const Map &) = default;
    private:
        MapResource<K, V> *resource;
        Map(MapResource<K, V> *resource)
        : resource(resource) {
            resource->reference_count++;
        }
    };
}

#endif