#pragma once
#ifndef FIKA_SERIALIZER_HPP
#define FIKA_SERIALIZER_HPP

#include "fika/objects/serializable_object.hpp"

namespace fika {

    class String;

    class Serializer {
    public:
        class Array {
        public:
            Array(Serializer *serializer)
            : serializer(serializer) {
                serializer->array_begin();
            }
            void end() {
                serializer->array_end();
            }
            template<typename T> void add(T value) {
                serializer->array_add(value);
            }
        private:
            Serializer *serializer;
        };
        class Object {
        public:
            Object(Serializer *serializer)
            : serializer(serializer) {

            }
            void end() {
                serializer->object_end();
            }
            template<typename T> void set_property(const String &name, T value) {
                serializer->object_set_property(name, value);
            }
        private:
            Serializer *serializer;
        };

        virtual Array array() {
            return Array(this);
        }
        virtual Object object() {
            return Object(this);
        }
        virtual void string(const String &str) = 0;
        virtual ~Serializer() {}
    protected:
        virtual void array_begin();
        virtual void array_end();
        /*virtual void array_add(I64 value);
        virtual void array_add(U64 value);
        virtual void array_add(I32 value);
        virtual void array_add(U32 value);
        virtual void array_add(I64 &value);
        virtual void array_add(U64 &value);
        virtual void array_add(void *value);
        virtual void array_add(const String &value);
        virtual void array_add(const SerializableObject &value);*/
        template<typename T> void array_add(T v) {
            // TODO: .... yeah...
        }
        virtual void object_begin();
        virtual void object_end();
        virtual void object_set_property(const String &name, I64 value);
        virtual void object_set_property(const String &name, U64 value);
        virtual void object_set_property(const String &name, const String &value);
        virtual void object_set_property(const String &name, const SerializableObject &value);
        
    };
}

#endif