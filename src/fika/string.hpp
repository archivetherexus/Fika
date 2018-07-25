#pragma once
#ifndef FIKA_STRING_HPP
#define FIKA_STRING_HPP

#include "object.hpp"
#include "fika/containers/immutable_array.hpp"

namespace fika {
    class String : public Object, public ImmutableArray<U32> {
    public:
        String(const char * c_string);
        virtual const class String to_string() const override;
        virtual const Hash to_hash() const override;
        virtual bool compare(ComparableObject *co) override {
            return ImmutableArray::compare(co);
        }
    };
}

#endif