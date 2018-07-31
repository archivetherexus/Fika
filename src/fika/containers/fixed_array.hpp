#pragma once
#ifndef FIKA_FIXED_ARRAY_HPP
#define FIKA_FIXED_ARRAY_HPP

#include "mutable_container.hpp"
#include "fika/iterator.hpp"
#include "fika/initializer_list.hpp"

namespace fika {
    template<U64 array_capacity, typename T> class FixedArrayIteratorState : public IteratorState<T> {
    public:
        U64 i = 0;
        FixedArrayIteratorState(U64 i): i(i) {}
        virtual IteratorState<T> *copy() const override {
            return new FixedArrayIteratorState<array_capacity, T>(i); 
        }
    };
    template<U64 array_capacity, typename T> class FixedArrayResource : public ContainerResource<T> {
    public:
        T data[array_capacity];
        virtual T next(IteratorState<T> *uncastedState, T *default_value) override {
            auto state = static_cast<FixedArrayIteratorState<array_capacity, T>*>(uncastedState);
            if (state->i < array_capacity) {
                return data[state->i++];
            } else {
                return *default_value;
            }
        }
        virtual bool has_next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<FixedArrayIteratorState<array_capacity, T>*>(uncastedState);
            return state->i < array_capacity;
        }
        FixedArrayResource()
        : ContainerResource<T>(0) {

        }
    };

    template<U64 array_capacity, typename T> class FixedArray : public MutableContainer<T> {
    public:
        static FixedArray<array_capacity, T> fill(T t) {
            auto resource = new FixedArrayResource<array_capacity, T>;

            for (U64 i = 0; i < array_capacity; i++) {
                resource->data[i] = t;
            }

            return FixedArray<array_capacity, T>(resource);
        }
        /*template<Length N> static Array<T> from(const T data[N]) {
            //static_assert(list.size() == array_capacity, "Incorrect size..."); // TODO: Better error message.
            // https://stackoverflow.com/questions/5438671/static-assert-on-initializer-listsize
            resource = new FixedArrayResource<T>(N);

            for (U64 i = 0; i < N; i++) {
                resource->data[i] = data[i];
            }

            return FixedArray<T>(resource);
        }*/
        static constexpr FixedArray<array_capacity, T> from(const std::initializer_list<T> list) {
            //list.size() > array_capacity ? static_assert(0, "FixedArray is too small to fit the initializer value.") : 0;
            //static_assert(list2.size() < array_capacity, "FixedArray is too small to fit the initializer value.");
            auto resource = new FixedArrayResource<array_capacity, T>;

            int i = 0;
            for (auto e: list) {
                resource->data[i++] = e;
            }

            return FixedArray<array_capacity, T>(resource);
        }
        FixedArray()
        : FixedArray(new FixedArrayResource<array_capacity, T>()) {
        }
        FixedArray(const FixedArray<array_capacity, T> &other)
        : FixedArray(other.resource) {
            // TODO: Could we move the copy constructor to the base class?
        }
        ~FixedArray() {
            if (0 == --resource->reference_count) {
                delete resource;
            }
        }
        virtual Iterator<T> iterator(T default_value) const override {
            return Iterator<T>(resource, new FixedArrayIteratorState<array_capacity, T>(0), default_value);
        }
        virtual void clear() override {

        }
        virtual U64 count() const override {
            return array_capacity;
        }
        
        FixedArray<array_capacity, T> operator=(std::initializer_list<T> list) {
            U64 i = 0 ;
            for (auto x : list) {
                resource->data[i++] = x;
                if (i >= array_capacity) {
                    break;
                }
            }
            return *this;
        }
    private:
        FixedArrayResource<array_capacity, T> *resource;
        FixedArray(FixedArrayResource<array_capacity, T> *resource)
        : resource(resource) {
            resource->reference_count++;
        }
    };
}

#endif