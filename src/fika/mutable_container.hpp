#pragma once
#ifndef FIKA_MUTABLE_CONTAINER_HPP
#define FIKA_MUTABLE_CONTAINER_HPP

#include "container.hpp"

namespace fika {
    template<typename T> class MutableContainer : public Container<T> {
    public:
        virtual void clear() = 0;
    };
}

#endif