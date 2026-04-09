#pragma once
#include "../../Renderer/VertexArray.hpp"

#include <cstdint>
#include <memory>

namespace zui {

class OpenglVertexArray : public VertexArray {
public:
    OpenglVertexArray();
    ~OpenglVertexArray() override;
    void Bind() const override;
    void Unbind() const override;

    void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
    void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;

    const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const override {
        return m_vertexBuffers;
    }
    const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override {
        return m_indexBuffer;
    }

private:
    std::uint32_t m_id = 0;
    std::uint32_t m_vertexBufferIndex = 0;
    std::vector<std::shared_ptr<VertexBuffer>> m_vertexBuffers;
    std::shared_ptr<IndexBuffer> m_indexBuffer;
};

} // namespace zui
