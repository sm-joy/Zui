#include "OpenglVertexBuffer.hpp"

#include <glad/gl.h>

namespace zui {
OpenglVertexBuffer::OpenglVertexBuffer(const float* vertices, std::uint32_t size) : m_size(size) {
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}

OpenglVertexBuffer::~OpenglVertexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void OpenglVertexBuffer::Bind() const {
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
}

void OpenglVertexBuffer::Unbind() const {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

OpenglIndexBuffer::OpenglIndexBuffer(const std::uint32_t* indices, std::uint32_t count) : m_count(count) {
    glCreateBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizeiptr>(count * sizeof(std::uint32_t)), indices, GL_STATIC_DRAW);
}

OpenglIndexBuffer::~OpenglIndexBuffer() {
    glDeleteBuffers(1, &m_id);
}

void OpenglIndexBuffer::Bind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
}

void OpenglIndexBuffer::Unbind() const {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

} // namespace zui
