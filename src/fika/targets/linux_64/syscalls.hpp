#pragma once
#ifndef FIKA_ARCH_SYSCALLS_HPP
#define FIKA_ARCH_SYSCALLS_HPP

namespace fika {
    enum Syscalls {
        WRITE = 0x1,
        ACCESS = 0x15,
    };
}

#endif