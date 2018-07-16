#pragma once
#ifndef FIKA_ITERATOR_HPP
#define FIKA_ITERATOR_HPP

#include "container.hpp"

namespace fika {
    template<class IteratorState, typename T> class Iterator {
    public:
        Iterator(ContainerResource *resource, IteratorState *state)
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
        ContainerResource<IteratorState, T> *resource;
        IteratorState *state;
    };
}

#endif