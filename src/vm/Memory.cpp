#include <vm/Memory.hpp>
#include <exception>

namespace zinc {
namespace vm {
    Memory::Memory()
        : m_alloc_ptr(nullptr)
        , m_size(0)
    {
    }

    void Memory::reserve(size_t size)
    {
        m_alloc_ptr = malloc(size);
        if (!m_alloc_ptr) {
            throw std::bad_alloc();
        }
        m_size = size;
        m_curr_ptr = m_alloc_ptr;
    }
}
}