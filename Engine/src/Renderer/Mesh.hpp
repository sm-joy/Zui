#pragma once
#include "../Core/API.hpp"

#include <cstdint>
#include <glm/glm.hpp>
#include <memory>
#include <vector>

namespace zui {
struct ZUI_API Vertex {
    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TexCoord;
};

class VertexArray;
class Material;

class ZUI_API Mesh {
public:
    struct SubMesh {
        std::uint32_t BaseVertex = 0;
        std::uint32_t BaseIndex = 0;
        std::uint32_t IndexCount = 0;
        std::uint32_t VertexCount = 0;
        std::uint32_t MaterialIndex = 0;
    };

    static std::shared_ptr<Mesh> Create(const std::vector<Vertex>& vertecies,
                                        const std::vector<std::uint32_t>& indices = {},
                                        const std::shared_ptr<Material>& material = nullptr);

    void Bind() const;
    void Unbind() const;

    const std::shared_ptr<VertexArray>& GetVertexArray() const { return m_vertexArray; }
    const std::vector<std::shared_ptr<Material>>& GetMaterials() const { return m_materials; }
    const std::vector<SubMesh>& GetSubMeshes() const { return m_subMeshes; }

    std::uint32_t GetIndexCount() const { return m_indexCount; }
    std::uint32_t GetVertexCount() const { return m_vertexCount; }

    bool IsIndexed() const { return m_indexCount > 0; }
    bool HasVertices() const { return m_vertexCount > 0; }

private:
    friend class MeshBuilder;

    explicit Mesh(const std::vector<Vertex>& vertecies, const std::vector<std::uint32_t>& indices,
                  std::vector<SubMesh> subMeshes = {}, std::vector<std::shared_ptr<Material>> materials = {});

    std::uint32_t m_indexCount = 0;
    std::uint32_t m_vertexCount = 0;

    std::shared_ptr<VertexArray> m_vertexArray;
    std::vector<SubMesh> m_subMeshes;
    std::vector<std::shared_ptr<Material>> m_materials;
};

class ZUI_API MeshBuilder {
public:
    explicit MeshBuilder(const std::vector<Vertex>& vertecies, const std::vector<std::uint32_t>& indices = {});
    MeshBuilder& AddSubMesh(std::uint32_t baseVertex, std::uint32_t baseIndex, std::uint32_t indexCount,
                            std::shared_ptr<Material> material = nullptr);

    MeshBuilder& AddSubMesh(std::uint32_t baseVertex, std::uint32_t vertexCount,
                            std::shared_ptr<Material> material = nullptr);

    std::shared_ptr<Mesh> Build();

private:
    bool m_hasSubMesh = false;
    std::shared_ptr<Mesh> m_mesh;
};

} // namespace zui