#pragma once
#ifndef FIKA_ITERATOR_HPP
#define FIKA_ITERATOR_HPP

#include "container.hpp"

#include <cstdio>

namespace fika {
    template<typename T> struct IteratorState {
        virtual IteratorState<T> *copy() const = 0;
        virtual ~IteratorState() {};
    };
    template<typename T> class Iterator {
    public:
        Iterator(ContainerResource<T> *resource, IteratorState<T> *state, T default_value)
        : resource(resource)
        , state(state)
        , default_value(default_value) {
            resource->reference_count++;
        }
        Iterator(const Iterator<T> &iterator)
        : resource(iterator.resource)
        , state(iterator.state->copy())
        , default_value(iterator.default_value) {
            this->resource->reference_count++;
        }
        ~Iterator() {
            resource->reference_count--;
            if (0 == resource->reference_count) {
                delete resource;
            }
            delete state;
        }
        T next() {
            return resource->next(state, &default_value);
        };
        bool has_next() {
            return resource->has_next(state);
        };
    private:
        ContainerResource<T> *resource;
        IteratorState<T> *state;
        T default_value;
    };
}

#endif