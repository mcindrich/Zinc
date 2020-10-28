#pragma once

namespace zinc {
namespace vm {
    enum class RegisterType {
        Unknown = 0,
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