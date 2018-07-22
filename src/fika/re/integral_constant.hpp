#pragma once
#ifndef FIKA_RE_INTEGRAL_CONSTANTS_HPP
#define FIKA_RE_INTEGRAL_CONSTANTS_HPP

namespace fika {
    namespace re {
        template<class T, T v> class IntegralConstant {
        public:
            static constexpr T value = v;
            typedef T value_type;
            typedef IntegralConstant type;
            constexpr operator value_type() const noexcept {
                return value;
            }
            constexpr value_type operator()() const noexcept {
                return value;
            }
        };
    }
}

#endif