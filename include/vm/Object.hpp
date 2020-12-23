#pragma once

#include <vector>

namespace zinc {
namespace vm {
    enum class ObjectType {
        Unknown = 0,
        Object,
        Enum,
        Function,
        Namespace,
    };

    class Object {
    public:
        Object();
        Object(ObjectType type);

    protected:
        // private data for each type
        void *m_priv;
        // objects one object posesses => methods, other objects, enums etc.
        std::vector<Object> m_objects;
        // type of a specific object
        ObjectType m_type;
    };
}
}