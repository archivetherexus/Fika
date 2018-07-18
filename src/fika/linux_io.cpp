#include "io.hpp"

// FIXME: We cheat here a bit... Since we use the stdlib...
extern "C" int putchar(int character);

namespace fika {
    StandardInputOutputStream io{};

    void StandardInputOutputStream::print_string(const String string) {
        auto iterator = string.iterator();
        while(iterator.has_next()) {
            putchar(iterator.next()); // TODO: Here we print an U32 by converting it to an U8... This is bad.
        }
    }
}