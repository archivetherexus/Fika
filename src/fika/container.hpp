#pragma once
#ifndef FIKA_CONTIANER_HPP
#define FIKA_CONTIANER_HPP

#include "types.hpp"

namespace fika {

    template <class IteratorState, typename T> class Iterator;

    template <class IteratorState, typename T> class ContainerResource {
    public:
        int referece_count;
        virtual T next(IteratorState *state) = 0;
        virtual bool has_next(IteratorState *state) = 0;
    };
    template <typename T> class Container {
        virtual Iterator<T> iterator() = 0;
        virtual void clear() = 0;
        virtual U64 count() = 0;
    };
}

#endif