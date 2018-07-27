#pragma once
#ifndef FIKA_ARRAY_HPP
#define FIKA_ARRAY_HPP

#include "mutable_container.hpp"
#include "fika/iterator.hpp"
#include "fika/initializer_list.hpp"

#include <cstdio>

namespace fika {
    template<typename T> class ArrayIteratorState : public IteratorState<T> {
    public:
        U64 i;
        ArrayIteratorState(U64 i): i(i) {}
        virtual IteratorState<T> *copy() const override {
            return new ArrayIteratorState<T>(i); 
        }
    };
    template<typename T> class ArrayResource : public ContainerResource<T> {
    public:
        U64 array_size;
        T *data = nullptr;

        ArrayResource(U64 array_size)
        : ContainerResource<T>(0)
        , array_size(array_size) {
            data = reinterpret_cast<T*>(operator new(sizeof(T) * array_size));
        }
        virtual T next(IteratorState<T> *uncastedState, T *default_value) override {
            auto state = static_cast<ArrayIteratorState<T>*>(uncastedState);
            if (state->i < array_size) {
                return data[state->i++];
            } else {
                return *default_value;
            }
        }
        virtual bool has_next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<ArrayIteratorState<T>*>(uncastedState);
            return state->i < array_size;
        }
        ~ArrayResource() {
            operator delete(reinterpret_cast<void*>(data));
        }
    };
    template<typename T> class Array : public MutableContainer<T> {
    public:
        static Array<T> fill(U64 array_size, T t) {
            auto resource = new ArrayResource<T>(array_size);

            for (U64 i = 0; i < array_size; i++) {
                resource->data[i] = t;
            }

            return Array<T>(resource);
        }
        static Array<T> from(std::initializer_list<T> list) {
            auto resource = new ArrayResource<T>(list.size());

            int i = 0;
            for (auto e: list) {
                resource->data[i++] = e;
            }

            return Array<T>(resource);
        }
        static Array<T> create(U64 array_size) {
            return Array<T>(new ArrayResource<T>(array_size));
        }
        ~Array() {
            resource->reference_count--;
            if (0 == resource->reference_count) { // FIXME: Convert to one liner.
                delete resource;
            }
        }
        virtual Iterator<T> iterator(T default_value) const override {
            return Iterator<T>(resource, new ArrayIteratorState<T>(0), default_value);
        }
        virtual void clear() override {
            // FIXME: Implement later.
        }
        virtual U64 count() const override {
            // FIXME: Implement later!
            return 0;
        }
        Array<T> operator=(std::initializer_list<T> list) {
            int i = 0 ;
            const U64 array_capacity = resource->array_size;
            for (auto x : list) {
                resource->data[i++] = x;
                if (i >= array_capacity) {
                    break;
                }
            }
            return *this;
        }
    private:
        ArrayResource<T> *resource;
        Array(ArrayResource<T> *resource)
        : resource(resource) {
            resource->reference_count++;
        }
    };
}

#endif