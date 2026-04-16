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

class ZUI_API Mesh {
public:
    static std::shared_ptr<Mesh> Create(const std::vector<Vertex>& vertecies,
                                        const std::vector<std::uint32_t>& indices = {});
                                        
    // static std::shared_ptr<Mesh> Load(const std::string& filepath); // to do
    // static std::shared_ptr<Mesh> Cube(); // to do

    void Bind() const;
    void Unbind() const;

    const std::shared_ptr<VertexArray>& GetVertexArray() const { return m_vertexArray; }
    std::uint32_t GetIndexCount() const { return m_indexCount; }
    std::uint32_t GetVertexCount() const { return m_vertexCount; }

    bool IsIndexed() const { return m_indexCount > 0; }
    bool HasVertices() const { return m_vertexCount > 0; }

private:
    explicit Mesh(const std::vector<Vertex>& vertecies, const std::vector<std::uint32_t>& indices = {});

    std::shared_ptr<VertexArray> m_vertexArray;
    std::uint32_t m_indexCount = 0;
    std::uint32_t m_vertexCount = 0;
};

} // namespace zui