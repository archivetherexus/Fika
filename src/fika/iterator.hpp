#pragma once
#ifndef FIKA_ITERATOR_HPP
#define FIKA_ITERATOR_HPP

#include "container.hpp"

namespace fika {
    template<typename T> class IteratorState {};
    template<typename T> class Iterator {
    public:
        Iterator(ContainerResource<T> *resource, IteratorState<T> *state)
        : resource(resource)
        , state(state) {
            resource->reference_count++;
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