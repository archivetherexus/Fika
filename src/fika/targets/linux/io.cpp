#include "fika/io.hpp"

#include "syscall.hpp"
#include "syscalls.hpp"

namespace fika {
    StandardInputOutputStream io{};

    void StandardInputOutputStream::print_string(const String string) {
        // FIXME: This is bad as we're converting U32 to char...
        char c[1];
        auto iterator = string.iterator(0);
        while(iterator.has_next()) {
            c[0] = iterator.next();
            fika_sysv_syscall(fika::Syscalls::ACCESS, 1, (Length)c, 1);
        }
    }
}