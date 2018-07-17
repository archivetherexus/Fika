#pragma once
#ifndef FIKA_INITIALIZER_LIST_HPP
#define FIKA_INITIALIZER_LIST_HPP

#include "types.hpp"

namespace std {
    template<class E>
    class initializer_list {
    private:
        const E*     array_data;
        fika::Length array_length;

        constexpr initializer_list(const E* array_data, fika::Length array_length)
        : array_data(array_data)
        , array_length(array_length) {

        }

    public:
        constexpr initializer_list() noexcept
        : array_data(0), array_length(0) {

        }
        constexpr fika::Length size() const noexcept {
            return array_length;
        }
        constexpr const E* begin() const noexcept {
            return array_data;
        }
        constexpr const E* end() const noexcept {
            return begin() + size();
        }
    };

    template<class E> constexpr const E* begin(initializer_list<E> from_initializer_list) noexcept {
        return from_initializer_list.begin();
    }

    template<class E> constexpr const E* end(initializer_list<E> from_initializer_list) noexcept {
        return from_initializer_list.end();
    }
}

#endif