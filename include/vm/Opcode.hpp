#pragma once

namespace zinc {
namespace vm {
    enum class Opcode : unsigned char {
        None,
        Move,
        Load,
        Store,
        Add,
        Sub,
        Mul,
        Div
    };
}
}