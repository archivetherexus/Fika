#pragma once
#ifndef FIKA_CONVERTERS_JSON_SERIALIZER_HPP
#define FIKA_CONVERTERS_JSON_SERIALIZER_HPP

#include "fika/serializer.hpp"
#include "fika/containers/mutable_container.hpp"

namespace fika {
    namespace converters {
        class JSONSerializer : public Serializer {
        public:
            MutableContainer<U32> &destination;
            JSONSerializer(MutableContainer<U32> &into)
            : destination(into) {

            }
            virtual void string(const String &str) override {
                destination.push('"');
                destination.push('.');
                destination.push('.');
                destination.push('.');
                destination.push('"');
            }
            virtual void array_begin() override {

            }
            virtual void array_end() override {

            }
        };
    }
}

#endif