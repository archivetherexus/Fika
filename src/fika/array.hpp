#pragma once
#ifndef FIKA_ARRAY_HPP
#define FIKA_ARRAY_HPP

#include "container.hpp"
#include "iterator.hpp"

namespace fika {
    template<typename T> class IteratorState;
    template<U64 array_capacity, typename T> class ArrayIteratorState : public IteratorState<T> {
    public:
        U64 i;
    };
    template<U64 array_capacity, typename T> class ArrayResource : public ContainerResource<T> {
    public:
        T data[array_capacity];
        virtual T next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<ArrayIteratorState<array_capacity, T>*>(uncastedState);
            if (state->i < array_capacity) {
                return data[state->i++];
            } else {
                return 0; // FIXME: There must be better way! Perhaps exceptions? Or default values...
            }
        }
        virtual bool has_next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<ArrayIteratorState<array_capacity, T>*>(uncastedState);
            return state->i < array_capacity;
        }
    };

    template<U64 array_capacity, typename T> class Array : public Container<T> {
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
        virtual Iterator<T> iterator() const override {
            return Iterator<T>(resource, new ArrayIteratorState<array_capacity, T>());
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