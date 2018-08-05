#pragma once
#ifndef FIKA_CONTIANER_HPP
#define FIKA_CONTIANER_HPP

#include "types.hpp"
#include "fika/objects/safe_object.hpp"
#include "fika/objects/serializable_object.hpp"
#include "fika/serializer.hpp"

namespace fika {

    template<typename T> class Iterator;
    template<typename T> class IteratorState;

    template<typename T> class ContainerResource {
    public:
        int reference_count = 0;
        ContainerResource(int reference_count)
        : reference_count(reference_count) {

        }
        virtual T next(IteratorState<T> *state, T *default_value) = 0;
        virtual bool has_next(IteratorState<T> *state) = 0;
        virtual ~ContainerResource() {
            
        };
    };
    template<typename T> class Container : public SafeObject, public SerializableObject {
    public:
        virtual Iterator<T> iterator(T default_value) const = 0;
        virtual U64 count() const = 0;
        virtual void serialize(Serializer *serializer) const override {
            auto array = serializer->array();
            T *tmp = reinterpret_cast<T*>(operator new(sizeof(T))); // TODO: Uhh...
            auto i = iterator(*tmp);
            while (i.has_next()) {
                array.add(i.next());
            }
            array.end();
            delete[] tmp;
        }
    };
}

#endif