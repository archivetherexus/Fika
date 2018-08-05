#pragma once
#ifndef FIKA_OBJECTS_SERIALIZABLE_OBJECT_HPP
#define FIKA_OBJECTS_SERIALIZABLE_OBJECT_HPP

namespace fika {
    class SerializableObject {
    public:
        virtual void serialize(class Serializer *serializer) const = 0;
        virtual ~SerializableObject() {};
    };
}

#endif