#pragma once
#ifndef FIKA_FIXED_ARRAY_HPP
#define FIKA_FIXED_ARRAY_HPP

#include "mutable_container.hpp"
#include "iterator.hpp"

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

    template<U64 array_capacity, typename T> class FixedArray : public MutableContainer<T> {
    public:
        FixedArray() {
            resource = new FixedArrayResource<array_capacity, T>();
            resource->reference_count++;
        }
        FixedArray(std::initializer_list<T> list) {
            //static_assert(list.size() == array_capacity, "Incorrect size..."); // TODO: Better error message.
            // https://stackoverflow.com/questions/5438671/static-assert-on-initializer-listsize
            resource = new FixedArrayResource<array_capacity, T>(list.size());
            resource->reference_count++;

            int i = 0;
            for (auto x : list) {
                resource->data[i++] = x;
            }
    
        }
        ~FixedArray() {
            resource->reference_count--;
            if (0 == resource->reference_count) { // FIXME: This could be merged into one statement.
                delete resource;
            }
        }
        virtual Iterator<T> iterator() const override {
            return Iterator<T>(resource, new FixedArrayIteratorState<array_capacity, T>(0));
        }
        virtual void clear() override {

        }
        virtual U64 count() const override {
            return array_capacity;
        }
        FixedArray<array_capacity, T> operator=(std::initializer_list<T> list) {
            int i = 0 ;
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
    };
}

#endif