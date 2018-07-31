#pragma once
#ifndef FIKA_ARCH_SYSCALL_HPP
#define FIKA_ARCH_SYSCALL_HPP

#include "types.hpp"

using namespace fika;

// Syscall list: 
// http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/
// TODO: Create a system call definition list.

extern "C" U64 fika_sysv_syscall(U64 rax, U64 rdi, Length rsi, U64 rdx);

#endif