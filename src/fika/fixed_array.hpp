#pragma once
#ifndef FIKA_FIXED_ARRAY_HPP
#define FIKA_FIXED_ARRAY_HPP

#include "container.hpp"
#include "iterator.hpp"

namespace fika {
    template<U64 array_capacity, typename T> class FixedArrayIteratorState : public IteratorState<T> {
    public:
        U64 i;
    };
    template<U64 array_capacity, typename T> class FixedArrayResource : public ContainerResource<T> {
    public:
        T data[array_capacity];
        virtual T next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<FixedArrayIteratorState<array_capacity, T>*>(uncastedState);
            if (state->i < array_capacity) {
                return data[state->i++];
            } else {
                return 0; // FIXME: There must be better way! Perhaps exceptions? Or default values...
            }
        }
        virtual bool has_next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<FixedArrayIteratorState<array_capacity, T>*>(uncastedState);
            return state->i < array_capacity;
        }
    };

    template<U64 array_capacity, typename T> class FixedArray : public Container<T> {
    public:
        FixedArray() {
            resource = new FixedArrayResource<array_capacity, T>();
            resource->reference_count++;
        }
        ~FixedArray() {
            resource->reference_count--;
            if (0 == resource->reference_count) { // FIXME: This could be merged into one statement.
                delete resource;
            }
        }
        virtual Iterator<T> iterator() const override {
            return Iterator<T>(resource, new FixedArrayIteratorState<array_capacity, T>());
        }
        virtual void clear() override {

        }
        virtual U64 count() const override {
            return array_capacity;
        }
    private:
        FixedArrayResource<array_capacity, T> *resource;
    };
}

#endif