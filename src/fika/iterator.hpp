#pragma once
#ifndef FIKA_ITERATOR_HPP
#define FIKA_ITERATOR_HPP

#include "container.hpp"

namespace fika {
    template<typename T> struct IteratorState {
        virtual IteratorState<T> *copy() const = 0;
    };
    template<typename T> class Iterator {
    public:
        Iterator(ContainerResource<T> *resource, IteratorState<T> *state)
        : resource(resource)
        , state(state) {
            resource->reference_count++;
        }
        Iterator(const Iterator<T> &iterator) {
            this->resource = iterator.resource;
            this->state = iterator.state->copy();
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
            return resource->next(state);
        };
        bool has_next() {
            return resource->has_next(state);
        };
    private:
        ContainerResource<T> *resource;
        IteratorState<T> *state;
    };
}

#endif