#pragma  once

#include "ShaderDataType.hpp"
#include "../Core/API.hpp"

#include <initializer_list>
#include <memory>
#include <vector>

namespace zui {

class BufferElement {
public:
    const char* Name;
    ShaderDataType Type;
    std::uint32_t Offset = 0;
    bool Normalized;

    BufferElement(ShaderDataType type, const char* name, bool normalized = false)
        : Name(name), Type(type), Normalized(normalized) {}

    std::uint32_t Size() const { return GetShaderDataTypeInfo(Type).Size; }
    std::uint32_t GetComponentCount() const { return GetShaderDataTypeInfo(Type).ComponentCount; }
    std::uint32_t GetColumnCount() const { return GetShaderDataTypeInfo(Type).ColumnCount; }
    std::uint32_t GetRowCount() const { return GetShaderDataTypeInfo(Type).RowCount; }
    ShaderDataBaseType GetBaseType() const { return GetShaderDataTypeInfo(Type).BaseType; }
};

class BufferLayout {
public:
    BufferLayout() = default;

    BufferLayout(const std::initializer_list<BufferElement>& elements) : m_bufferElements(elements) {
        CalculateOffsetsAndStride();
    }

    std::uint32_t GetStride() const { return m_stride; }
    const std::vector<BufferElement>& GetBufferElements() const { return m_bufferElements; }
    
private:
    void CalculateOffsetsAndStride() {
        std::uint32_t offset = 0;
        m_stride = 0;
        for (BufferElement& element : m_bufferElements) {
            element.Offset = offset;
            offset += element.Size();
            m_stride += element.Size();
        }
    }

    std::vector<BufferElement> m_bufferElements;
    std::uint32_t m_stride = 0;
};

class ZUI_API VertexBuffer {
public:
    virtual ~VertexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual void SetLayout(const BufferLayout& layout) = 0;
    virtual const BufferLayout& GetBufferLayout() const = 0;
    virtual std::uint32_t GetSize() const = 0;

    static std::shared_ptr<VertexBuffer> Create(const float* vertices, std::uint32_t size);
};

class ZUI_API IndexBuffer {
public:
    virtual ~IndexBuffer() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual std::uint32_t GetCount() const = 0;

    static std::shared_ptr<IndexBuffer> Create(const std::uint32_t* indices, std::uint32_t count);
};

} // namespace zui
