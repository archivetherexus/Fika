#pragma once
#ifndef FIKA_SYSCALL_HPP
#define FIKA_SYSCALL_HPP

#include "types.hpp"

using namespace fika;

extern "C" void fika_syscall(u32 eax, u32 ebx, u32 ecx, u32 edx);

#endif