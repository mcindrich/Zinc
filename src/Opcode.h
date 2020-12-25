#include <bits/stdint-uintn.h>
#pragma once

namespace zinc {
namespace vm {
    enum class Opcode {
        Unknown = 0,
        Add,
        Sub,
        Mul,
        Div,
        Load,
        Store,
        Jump,
        Call,
        Ret,
    };
}
}