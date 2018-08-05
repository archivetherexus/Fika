#pragma once
#ifndef FIKA_OBJECTS_PRINTABLE_OBJECT_HPP
#define FIKA_OBJECTS_PRINTABLE_OBJECT_HPP

namespace fika {
    class PrintableObject {
    public:
        virtual const class String to_string() const = 0;
    };
}

#endif