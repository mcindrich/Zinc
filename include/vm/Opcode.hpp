#pragma once

namespace zinc {
namespace vm {
    enum class Opcode {
        HALT = 0,
        ADD,
        SUB,
        MUL,
        DIV
    };
}
}