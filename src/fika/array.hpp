#pragma once
#ifndef FIKA_ARRAY_HPP
#define FIKA_ARRAY_HPP

#include "container.hpp"

namespace fika {

    template<U64 array_capacity, typename T> class ArrayIteratorState {
    public:
        U64 i;
    };
    template<U64 array_capacity, typename T> class ArrayResource : private ContainerResource<ArrayIteratorState<array_capacity, T>, T> {
    public:
        T data[array_capacity];
        virtual T next(ArrayIteratorState<array_capacity, T> *state) override {
            if (state->i < array_capacity) {
                return data[state->i++];
            } else {
                return 0; // FIXME: There must be better way! Perhaps exceptions? Or default values...
            }
        }
        virtual bool has_next(ArrayIteratorState<array_capacity, T> *state) override {
            return state->i < array_capacity;
        }
    };

    template<U64 array_capacity, typename T> class Array : Container<T> {
    public:
        Array() {
            resource = new ArrayResource<array_capacity, T>();
            resource->reference_count++;
        }
        ~Array() {
            resource->reference_count--;
            if (0 == resource->reference_count) { // FIXME: This could be merged into one statement.
                delete resource;
            }
        }
        virtual Iterator<ArrayIteratorState<array_capacity, T>, T> iterator() override {
            return Iterator<ArrayIteratorState<array_capacity, T>, T>(resource);
        }
        virtual void clear() override {

        }
        virtual U64 count() override {
            return array_capacity;
        }
    private:
        ArrayResource<array_capacity, T> *resource;
    };
}

#endif