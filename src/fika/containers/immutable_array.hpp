#pragma once
#ifndef FIKA_IMMUTABLE_ARRAY_HPP
#define FIKA_IMMUTABLE_ARRAY_HPP

#include "fika/empty.hpp"
#include "fika/container.hpp"
#include "fika/iterator.hpp"
#include "fika/initializer_list.hpp"
#include "fika/objects/comparable_object.hpp"

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

        ImmutableArrayResource(U64 reference_count, U64 array_size)
        : ContainerResource<T>(reference_count)
        , array_size(array_size) {
            data = reinterpret_cast<T*>(operator new(sizeof(T) * array_size));
        }
        ~ImmutableArrayResource() {
            delete data;
        }
        virtual T next(IteratorState<T> *uncastedState, T *default_value) override {
            auto state = static_cast<ImmutableArrayIteratorState<T>*>(uncastedState);
            if (state->i < array_size) {
                return data[state->i++];
            } else {
                return *default_value;
            }
        }
        virtual bool has_next(IteratorState<T> *uncastedState) override {
            auto state = static_cast<ImmutableArrayIteratorState<T>*>(uncastedState);
            return state->i < array_size;
        }
    };

    extern ImmutableArrayResource<Empty> *empty_immutable_array_resource;

    template<typename T> class ImmutableArray : public ComparableObject, public Container<T> {
    public:
        static ImmutableArray<T> empty() {
            return ImmutableArray<T>(reinterpret_cast<ImmutableArrayResource<T>*>(empty_immutable_array_resource));
        }
        static ImmutableArray<T> fill(U64 array_size, T t) {
            auto resource = new ImmutableArrayResource<T>(0, array_size);

            for (U64 i = 0; i < array_size; i++) {
                resource->data[i] = t;
            }

            return ImmutableArray<T>(resource);
        }
        /*template<Length N> static ImmutableArray<T> from(const T data[N]) {
            auto resource = new ImmutableArrayResource<T>(0, N);

            for (U64 i = 0; i < N; i++) {
                resource->data[i] = data[i];
            }

            return ImmutableArray<T>(resource);

            TODO: Renable this some day.... Maybe detect GCC version??
        }*/
        static ImmutableArray<T> from(std::initializer_list<T> list) {
            auto resource = new ImmutableArrayResource<T>(0, list.size());

            int i = 0;
            for (auto e: list) {
                resource->data[i++] = e;
            }

            return ImmutableArray<T>(resource);
        }

        ImmutableArray(const ImmutableArray<T> &immutable_array) {
            this->resource = immutable_array.resource;
            this->resource->reference_count++;
        }
        ~ImmutableArray() {
            resource->reference_count--;
            if (0 == resource->reference_count) { // FIXME: Convert to one liner.
                delete resource;
            }
        }
        virtual Iterator<T> iterator(T default_value) const override {
            return Iterator<T>(resource, new ImmutableArrayIteratorState<T>(0), default_value);
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
        ImmutableArray(ImmutableArrayResource<T> *resource)
        : resource(resource) {
            resource->reference_count++;
        }
        ImmutableArray()
        : resource(nullptr) {

        }

    };
}

#endif