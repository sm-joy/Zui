#pragma once
#include "../../Renderer/VertexBuffer.hpp"

namespace zui {

class OpenglVertexBuffer : public VertexBuffer {
public:
    OpenglVertexBuffer(const float* vertices, std::uint32_t size);
    ~OpenglVertexBuffer() override;

    void Bind() const override;
    void Unbind() const override;
    void SetLayout(const BufferLayout& layout) override { m_bufferLayout = layout; };
    const BufferLayout& GetBufferLayout() const override { return m_bufferLayout; };

private:
    std::uint32_t m_id = 0;
    BufferLayout m_bufferLayout;
};

class OpenglIndexBuffer : public IndexBuffer {
public:
    OpenglIndexBuffer(const std::uint32_t* indices, std::uint32_t count);
    ~OpenglIndexBuffer() override;

    void Bind() const override;
    void Unbind() const override;

    std::uint32_t GetCount() const override { return m_count; }
private:
    std::uint32_t m_id = 0;
    std::uint32_t m_count = 0;
};

} // namespace zui
