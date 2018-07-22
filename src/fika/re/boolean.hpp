#pragma once
#ifndef FIKA_RE_BOOLEAN_HPP
#define FIKA_RE_BOOLEAN_HPP

#include "integral_constant.hpp"

namespace fika {
    namespace re {
        typedef IntegralConstant<bool, true> True;
        typedef IntegralConstant<bool, false> False;
    }
}

#endif