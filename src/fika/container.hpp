#pragma once
#ifndef FIKA_CONTIANER_HPP
#define FIKA_CONTIANER_HPP

#include "types.hpp"

namespace fika {

    template<typename T> class Iterator;
    template<typename T> class IteratorState;

    template<typename T> class ContainerResource {
    public:
        int reference_count = 0;
        virtual T next(IteratorState<T> *state) = 0;
        virtual bool has_next(IteratorState<T> *state) = 0;
    };
    template<typename T> class Container {
        virtual Iterator<T> iterator() const = 0;
        virtual U64 count() const = 0;
    };
}

#endif