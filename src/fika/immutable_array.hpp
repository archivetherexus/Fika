#pragma once
#ifndef FIKA_IMMUTABLE_ARRAY_HPP
#define FIKA_IMMUTABLE_ARRAY_HPP

#include "container.hpp"
#include "initializer_list.hpp"
#include "iterator.hpp"

namespace fika {
    template<typename T> class ImmutableArrayIteratorState : public IteratorState<T> {
    public:
        U64 i;
        ImmutableArrayIteratorState(U64 i): i(i) {}
        virtual IteratorState<T> *copy() const override {
            return new ImmutableArrayIteratorState<T>{i}; 
        }
    };
    template<typename T> class ImmutableArrayResource : public ContainerResource<T> {
    public:
        U64 array_size;
        T *data = nullptr;

        ImmutableArrayResource(U64 array_size)
        : array_size(array_size) {
            data = new T[array_size];
        }
        virtual T next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<ImmutableArrayIteratorState<T>*>(uncastedState);
            if (state->i < array_size) {
                return data[state->i++];
            } else {
                return 0; // FIXME: There must be better way! Perhaps exceptions? Or default values...
            }
        }
        virtual bool has_next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<ImmutableArrayIteratorState<T>*>(uncastedState);
            return state->i < array_size;
        }
    };
    template<typename T> class ImmutableArray : public ComparableObject, public Container<T> {
    public:
        ImmutableArray()
        : ImmutableArray(0) {
        }
        ImmutableArray(U64 array_size) {
            resource = new ImmutableArrayResource<T>(array_size);
            resource->reference_count++;
        }
        ImmutableArray(const ImmutableArray<T> &immutable_array) {
            this->resource = immutable_array.resource;
            this->resource->reference_count++;
        }
        ImmutableArray(std::initializer_list<T> list) {
            resource = new ImmutableArrayResource<T>(list.size());
            resource->reference_count++;

            int i = 0;
            for (auto x : list) {
                resource->data[i++] = x;
            }
        }
        ~ImmutableArray() {
            resource->reference_count--;
            if (0 == resource->reference_count) { // FIXME: Convert to one liner.
                delete resource;
            }
        }
        virtual Iterator<T> iterator() const override {
            return Iterator<T>(resource, new ImmutableArrayIteratorState<T>(0));
        }
        virtual U64 count() const override {
            // FIXME: Implement later!
            return resource->array_size;
        }
        virtual bool compare(ComparableObject *co) override {
            if (co == this) {
                return true;
            } else if (auto other = dynamic_cast<ImmutableArray<T>*>(co)) {
                ImmutableArrayResource<T>* r = other->resource;
                if (r->array_size == resource->array_size) {
                    return false;
                }
                for (U64 i = 0; i < r->array_size; i++) {
                    if (r->data[i] != resource->data[i]) {
                        return false;
                    }
                }
                return true;
            } else {
                return false;
            }
        }
    protected:
        ImmutableArrayResource<T> *resource;
    };
}

#endif