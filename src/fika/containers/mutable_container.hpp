#pragma once
#ifndef FIKA_CONTAINERS_MUTABLE_CONTAINER_HPP
#define FIKA_CONTAINERS_MUTABLE_CONTAINER_HPP

#include "fika/container.hpp"

namespace fika {
    template<typename T> class MutableContainer : public Container<T> {
    public:
        virtual void clear() = 0;
        virtual void push(T value) = 0;
    };
}

#endif