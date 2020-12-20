#pragma once

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
        void *m_priv;
        ObjectType m_type;
    };
}
}