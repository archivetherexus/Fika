#include "io.hpp"

// FIXME: We cheat here a bit...
#include <stdio.h>

namespace fika {
    StandardInputOutputStream io{};

    void StandardInputOutputStream::print_string(const String &string) {
        // FIXME: We cheat here a bit...
        printf("Reached point A!\n");
    }
}