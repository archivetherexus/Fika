#pragma once
#ifndef FIKA_IO_HPP
#define FIKA_IO_HPP

#include "input_stream.hpp"
#include "output_stream.hpp"
#include "string.hpp"

namespace fika {
    class InputOutputStream : public OutputStream, public InputStream {};

    class StandardInputOutputStream : public InputOutputStream {
    public:
        virtual void print_string(const String &string) override;
    };

    extern StandardInputOutputStream io;
}

#endif