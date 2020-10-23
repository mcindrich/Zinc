#pragma once

#include <cstdlib>

namespace zinc {
namespace vm {
    class Memory {
    public:
        Memory();
        void reserve(size_t size);

    private:
        void *m_alloc_ptr;
        void *m_curr_ptr;
        size_t m_size;
    };
}
}