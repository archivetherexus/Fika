#pragma once
#ifndef FIKA_ARCH_TYPES_HPP
#define FIKA_ARCH_TYPES_HPP


// TODO: Perhaps move or rename this **file** to avoid name clashes...

namespace fika {
    typedef signed char      I8;
    typedef signed short     I16;
    typedef signed int       I32;
    typedef signed long long I64;

    typedef unsigned char      U8;
    typedef unsigned short     U16;
    typedef unsigned int       U32;
    typedef unsigned long long U64;

    typedef long unsigned int Length;
}

#endif