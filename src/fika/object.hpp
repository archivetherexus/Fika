#pragma once
#ifndef FIKA_OBJECT_HPP
#define FIKA_OBJECT_HPP

#include "fika/objects/printable_object.hpp"
#include "fika/objects/hashable_object.hpp"
#include "fika/objects/safe_object.hpp"
#include "fika/objects/comparable_object.hpp"
#include "fika/objects/serializable_object.hpp"

namespace fika {
    class Object : public PrintableObject, public HashableObject, public ComparableObject, public SafeObject, public SerializableObject {

    };
}

#endif