#include "Mesh.hpp"

#include "Material.hpp"
#include "ShaderDataType.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"

#include <memory>

namespace zui {

Mesh::Mesh(const std::vector<Vertex>& vertecies, const std::vector<std::uint32_t>& indices,
           std::vector<SubMesh> subMeshes, std::vector<std::shared_ptr<Material>> materials)
    : m_indexCount(static_cast<std::uint32_t>(indices.size())),
      m_vertexCount(static_cast<std::uint32_t>(vertecies.size())) {
    if (!subMeshes.empty()) {
        m_subMeshes = std::move(subMeshes);
    }

    if (!materials.empty()) {
        m_materials = std::move(materials);
    }

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

std::shared_ptr<Mesh> Mesh::Create(const std::vector<Vertex>& vertecies, const std::vector<uint32_t>& indices,
                                   const std::shared_ptr<Material>& material) {
    Mesh::SubMesh subMesh = {.IndexCount = static_cast<std::uint32_t>(indices.size()),
                             .VertexCount = static_cast<std::uint32_t>(vertecies.size())};
    std::vector<Mesh::SubMesh> subMeshes = {subMesh};
    std::vector<std::shared_ptr<Material>> materials;
    if (material) {
        materials.push_back(material);
    }
    return std::shared_ptr<Mesh>(new Mesh(vertecies, indices, subMeshes, materials));
}

void Mesh::Bind() const {
    m_vertexArray->Bind();
}

void Mesh::Unbind() const {
    m_vertexArray->Unbind();
}

MeshBuilder::MeshBuilder(const std::vector<Vertex>& vertices, const std::vector<std::uint32_t>& indices) {
    m_mesh = std::shared_ptr<Mesh>(new Mesh(vertices, indices));
}

MeshBuilder& MeshBuilder::AddSubMesh(std::uint32_t baseVertex, std::uint32_t baseIndex, std::uint32_t indexCount,
                                     std::shared_ptr<Material> material) {
    m_hasSubMesh = true;
    Mesh::SubMesh sub = {.BaseVertex = baseVertex,
                         .BaseIndex = baseIndex,
                         .IndexCount = indexCount,
                         .VertexCount = 0,
                         .MaterialIndex = static_cast<std::uint32_t>(m_mesh->m_materials.size())};

    m_mesh->m_subMeshes.push_back(sub);
    m_mesh->m_materials.push_back(material);
    return *this;
}

MeshBuilder& MeshBuilder::AddSubMesh(std::uint32_t baseVertex, std::uint32_t vertexCount,
                                     std::shared_ptr<Material> material) {
    m_hasSubMesh = true;
    Mesh::SubMesh sub = {.BaseVertex = baseVertex,
                         .BaseIndex = 0,
                         .IndexCount = 0,
                         .VertexCount = vertexCount,
                         .MaterialIndex = static_cast<std::uint32_t>(m_mesh->m_materials.size())};

    m_mesh->m_subMeshes.push_back(sub);
    m_mesh->m_materials.push_back(material);
    return *this;
}

std::shared_ptr<Mesh> MeshBuilder::Build() {
    if (m_hasSubMesh) {
        return m_mesh;
    }
    return nullptr;
}

} // namespace zui