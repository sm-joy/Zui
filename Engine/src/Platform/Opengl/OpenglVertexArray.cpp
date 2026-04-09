#include "OpenglVertexArray.hpp"

#include "../../Logger/Log.hpp"
#include "../../Renderer/ShaderDataType.hpp"

#include <cstdint>
#include <glad/gl.h>

namespace zui {

static GLenum ShaderDataBaseTypeToOpenglBaseType(ShaderDataBaseType baseType) {
    switch (baseType) {
    case ShaderDataBaseType::FLOAT:
        return GL_FLOAT;
    case ShaderDataBaseType::INT:
        return GL_INT;
    case ShaderDataBaseType::BOOL:
        return GL_UNSIGNED_BYTE;
    case ShaderDataBaseType::NONE:
    default:
        LOGGER_ERROR("Unknown ShaderDataType");
        return 0;
    }
}

inline static GLenum IsNormalized(bool normalized) {
    return normalized ? GL_TRUE : GL_FALSE;
}

OpenglVertexArray::OpenglVertexArray() {
    glCreateVertexArrays(1, &m_id);
}
OpenglVertexArray::~OpenglVertexArray() {
    glDeleteVertexArrays(1, &m_id);
}
void OpenglVertexArray::Bind() const {
    glBindVertexArray(m_id);
}
void OpenglVertexArray::Unbind() const {
    glBindVertexArray(0);
}

void OpenglVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) {
    if (!vertexBuffer) {
        LOGGER_ERROR("VertexBuffer is null.");
        return;
    }

    if (vertexBuffer->GetBufferLayout().GetBufferElements().empty()) {
        LOGGER_WARN("VertexBuffer has no layout set");
        return;
    }

    glBindVertexArray(m_id);
    vertexBuffer->Bind();

    const BufferLayout& bufferLayout = vertexBuffer->GetBufferLayout();

    for (const BufferElement& bufferElement : bufferLayout.GetBufferElements()) {
        const GLenum baseType = ShaderDataBaseTypeToOpenglBaseType(bufferElement.GetBaseType());
        const std::uint32_t columnCount = std::max<std::uint32_t>(1, bufferElement.GetColumnCount());
        const std::uint32_t rowCount = std::max<std::uint32_t>(1, bufferElement.GetRowCount());
        const std::uint32_t bytesPerColumn = bufferElement.Size() / columnCount;

        for (std::uint32_t column = 0; column < columnCount; ++column) {
            const std::uintptr_t offset = static_cast<std::uintptr_t>(bufferElement.Offset) + static_cast<std::uintptr_t>(bytesPerColumn) * column;

            glEnableVertexAttribArray(m_vertexBufferIndex);

            if (bufferElement.GetBaseType() == ShaderDataBaseType::INT
                || bufferElement.GetBaseType() == ShaderDataBaseType::BOOL) {
                glVertexAttribIPointer(m_vertexBufferIndex, static_cast<int>(rowCount), baseType,
                                       static_cast<int>(bufferLayout.GetStride()),
                                       reinterpret_cast<const void*>(offset));
            } else {
                glVertexAttribPointer(
                    m_vertexBufferIndex, static_cast<int>(rowCount), baseType, IsNormalized(bufferElement.Normalized),
                    static_cast<int>(bufferLayout.GetStride()), reinterpret_cast<const void*>(offset));
            }

            ++m_vertexBufferIndex;
        }
    }

    m_vertexBuffers.push_back(vertexBuffer);
}

void OpenglVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) {
    glBindVertexArray(m_id);
    indexBuffer->Bind();
    m_indexBuffer = indexBuffer;
}

} // namespace zui
