#pragma once
#ifndef PRINTABLE_OBJECT_HPP
#define PRINTABLE_OBJECT_HPP

namespace fika {
    class PrintableObject {
    public:
        virtual const class String to_string() const = 0;
    };
}

#endif