#pragma once

#include <memory>

namespace zinc {
namespace vm {
    class Object {

    private:
        std::unique_ptr<void> m_priv;
    };
}
}