#pragma once

namespace zinc {
namespace vm {
    enum class RegisterType {
        NATURAL = 0,
        INTEGER,
        RATIONAL,
        REAL,
        COMPLEX,
    };
    class Register {
    public:
        Register();

    private:
        void *m_val;
        RegisterType m_type;
    };
}
}