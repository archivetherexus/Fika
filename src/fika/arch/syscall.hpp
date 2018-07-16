#pragma once
#ifndef FIKA_SYSCALL_HPP
#define FIKA_SYSCALL_HPP

#include "types.hpp"

using namespace fika;

extern "C" void fika_syscall(U32 eax, U32 ebx, U32 ecx, U32 edx);

#endif