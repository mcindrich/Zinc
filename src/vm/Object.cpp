#include <vm/Object.hpp>

namespace zinc {
namespace vm {
    Object::Object()
        : Object(ObjectType::Unknown)
    {
    }

    Object::Object(ObjectType type)
        : m_type(type)
        , m_priv(nullptr)
    {
    }
}
}