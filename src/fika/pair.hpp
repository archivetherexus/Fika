#pragma once
#ifndef FIKA_PAIR_HPP
#define FIKA_PAIR_HPP

namespace fika {
    template<typename A, typename B> class Pair {
    public:
        A const a;
        B const b;

        Pair(A a, B b)
        : a(a), b(b) {

        }
    };
}

#endif