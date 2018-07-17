#pragma once
#ifndef FIKA_ARRAY_HPP
#define FIKA_ARRAY_HPP

#include "container.hpp"

namespace fika {
    template<typename T> class ArrayIteratorState : public IteratorState<T> {
    public:
        U64 i;
    };
    template<typename T> class ArrayResource : public ContainerResource<T> {
    public:
        U64 array_size;
        T *data = nullptr;

        ArrayResource(U64 array_size)
        : array_size(array_size) {
            data = new T[array_size];
        }
        virtual T next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<ArrayIteratorState<T>*>(uncastedState);
            if (state->i < array_size) {
                return data[state->i++];
            } else {
                return 0; // FIXME: There must be better way! Perhaps exceptions? Or default values...
            }
        }
        virtual bool has_next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<ArrayIteratorState<T>*>(uncastedState);
            return state->i < array_size;
        }
    };
    template<typename T> class Array : public Container<T> {
    public:
        Array(U64 array_size) {
            resource = new ArrayResource<T>(array_size);
            resource->reference_count++;
        }
        ~Array() {
            resource->reference_count--;
            if (0 == resource->reference_count) { // FIXME: Convert to one liner.
                delete resource;
            }
        }
        virtual Iterator<T> iterator() const override {
            return Iterator<T>(resource, new ArrayIteratorState<T>());
        }
        virtual void clear() override {
            // FIXME: Implement later.
        }
        virtual U64 count() const override {
            // FIXME: Implement later!
            return 0;
        }
    private:
        ArrayResource<T> *resource;
    };
}

#endif