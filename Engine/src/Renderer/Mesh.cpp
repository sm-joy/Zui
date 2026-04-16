#include "Mesh.hpp"

#include "ShaderDataType.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

#include <memory>

namespace zui {

Mesh::Mesh(const std::vector<Vertex>& vertecies, const std::vector<uint32_t>& indices)
    : m_indexCount(static_cast<std::uint32_t>(indices.size())),
      m_vertexCount(static_cast<std::uint32_t>(vertecies.size())) {
    m_vertexArray = VertexArray::Create();
    std::shared_ptr<VertexBuffer> vb =
        VertexBuffer::Create((float*)(vertecies.data()), static_cast<std::uint32_t>(vertecies.size() * sizeof(Vertex)));

    vb->SetLayout({{ShaderDataType::FLOAT3, "a_Position"},
                   {ShaderDataType::FLOAT3, "a_Normal"},
                   {ShaderDataType::FLOAT2, "a_TexCoord"}});

    m_vertexArray->AddVertexBuffer(vb);
    
    if (!indices.empty()) {
        std::shared_ptr<IndexBuffer> ib =
            IndexBuffer::Create((std::uint32_t*)indices.data(), static_cast<std::uint32_t>(indices.size()));
    
        m_vertexArray->SetIndexBuffer(ib);
    }
}

std::shared_ptr<Mesh> Mesh::Create(const std::vector<Vertex>& vertecies, const std::vector<uint32_t>& indices) {
    return std::shared_ptr<Mesh>(new Mesh(vertecies, indices));
}

void Mesh::Bind() const {
    m_vertexArray->Bind();
}

void Mesh::Unbind() const {
    m_vertexArray->Unbind();
}

} // namespace zui