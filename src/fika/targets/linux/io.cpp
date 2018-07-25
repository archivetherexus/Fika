#include "fika/io.hpp"

#include "syscall.hpp"

namespace fika {
    StandardInputOutputStream io{};

    void StandardInputOutputStream::print_string(const String string) {
        // FIXME: This is bad as we're converting U32 to char...
        char c[1];
        auto iterator = string.iterator(0);
        while(iterator.has_next()) {
            c[0] = iterator.next();
            fika_sysv_syscall(1, 1, (Length)c, 1);
        }
    }
}