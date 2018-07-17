#pragma once
#ifndef FIKA_IMMUTABLE_ARRAY_HPP
#define FIKA_IMMUTABLE_ARRAY_HPP

#include "container.hpp"
#include "initializer_list.hpp"

namespace fika {
    template<typename T> class ImmutableArrayIteratorState : public IteratorState<T> {
    public:
        U64 i;
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
    template<typename T> class ImmutableArray : public Container<T> {
    public:
        ImmutableArray()
        : ImmutableArray(0) {
        }
        ImmutableArray(U64 array_size) {
            resource = new ImmutableArrayResource<T>(array_size);
            resource->reference_count++;
        }
        ImmutableArray(std::initializer_list<T> list) {
            resource = new ImmutableArrayResource<T>(list.size());
            resource->reference_count++;

            int i = 0 ;
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
            return Iterator<T>(resource, new ImmutableArrayIteratorState<T>());
        }
        virtual void clear() override {
            // FIXME: Implement later.
        }
        virtual U64 count() const override {
            // FIXME: Implement later!
            return 0;
        }

        /*

        DOING THIS DOESN'T MAKE SENSE.
        Why?
        Well, haha, because these arrays are immutable.
        But this code can be usefull for when array.hpp is implemented...

        ImmutableArray<T> operator=(std::initializer_list<T> list) {
            resource->reference_count--;
            if (0 == resource->reference_count) { // FIXME: Convert to one liner.
                delete resource;
            }
            // This is somewhat inefficient... We could for instance check the current sign...

            resource = new ImmutableArrayResource<T>(list.size());
            resource->reference_count++;

            int i = 0 ;
            for (auto x : list) {
                resource->data[i++] = x;
            }


            return *this; // FIXME: Is this the correct implementation?
        }
        */
    private:
        ImmutableArrayResource<T> *resource;
    };
}

#endif