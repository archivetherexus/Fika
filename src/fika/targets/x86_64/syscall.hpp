#pragma once
#ifndef FIKA_SYSCALL_HPP
#define FIKA_SYSCALL_HPP

#include "types.hpp"

using namespace fika;

extern "C" U64 fika_sysv_syscall(U64 eax, U64 ebx, Length ecx, U64 edx);

#endif