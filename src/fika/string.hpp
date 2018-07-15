#pragma once
#ifndef FIKA_STRING_HPP
#define FIKA_STRING_HPP

#include "object.hpp"

namespace fika {
    class String : public Object {
    public:
        virtual const class String &to_string() const override;
    };
}

#endif