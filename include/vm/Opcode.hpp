#pragma once

namespace zinc {
namespace vm {
    enum class Opcode : unsigned char {
        None = 0,
        Move,
        Load,
        Store,
        Add,
        Sub,
        Mul,
        Div,
        Jump,
        Call,
        Ret,
    };
}
}