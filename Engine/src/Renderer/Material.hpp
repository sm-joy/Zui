#pragma once
#include "../Core/API.hpp"

#include <cstdint>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>

namespace zui {

class MaterialInstance;
class Shader;
class Texture2D;

class ZUI_API Material : public std::enable_shared_from_this<Material> {
public:
    static std::shared_ptr<Material> Create(const std::shared_ptr<Shader>& shader);

    void SetInt(const std::string& name, int value) { m_ints[name] = value; }
    void SetFloat(const std::string& name, float value) { m_floats[name] = value; }
    void SetFloat2(const std::string& name, const glm::vec2& value) { m_vec2s[name] = value; }
    void SetFloat3(const std::string& name, const glm::vec3& value) { m_vec3s[name] = value; }
    void SetFloat4(const std::string& name, const glm::vec4& value) { m_vec4s[name] = value; }
    void SetMat2(const std::string& name, const glm::mat2& value) { m_mat2s[name] = value; }
    void SetMat3(const std::string& name, const glm::mat3& value) { m_mat3s[name] = value; }
    void SetMat4(const std::string& name, const glm::mat4& value) { m_mat4s[name] = value; }
    void SetTexture(const std::string& name, const std::shared_ptr<Texture2D>& tex);

    void Bind() const;
    void Unbind() const;

    const std::shared_ptr<Shader>& GetShader() const { return m_shader; }

    std::shared_ptr<MaterialInstance> CreateInstance();

private:
    explicit Material(const std::shared_ptr<Shader>& shader) : m_shader(shader) {}

    std::shared_ptr<Shader> m_shader;

    std::unordered_map<std::string, int> m_ints;
    std::unordered_map<std::string, float> m_floats;
    std::unordered_map<std::string, glm::vec2> m_vec2s;
    std::unordered_map<std::string, glm::vec3> m_vec3s;
    std::unordered_map<std::string, glm::vec4> m_vec4s;
    std::unordered_map<std::string, glm::mat2> m_mat2s;
    std::unordered_map<std::string, glm::mat3> m_mat3s;
    std::unordered_map<std::string, glm::mat4> m_mat4s;

    struct TextureBinding {
        std::shared_ptr<Texture2D> Texture;
        std::uint32_t Slot;
    };
    std::unordered_map<std::string, TextureBinding> m_textures;
    std::uint32_t m_nextTextureSlot = 0;
};

class ZUI_API MaterialInstance {
public:
    MaterialInstance(const std::shared_ptr<Material>& parent) : m_parent(parent) {}

    void SetFloat3(const std::string& name, const glm::vec3& value) { m_vec3s[name] = value; }
    void SetFloat4(const std::string& name, const glm::vec4& value) { m_vec4s[name] = value; }
    void SetTexture(const std::string& name, const std::shared_ptr<Texture2D>& tex);

    void Bind() const;
    void Unbind() const;
    const std::shared_ptr<Shader>& GetShader() const { return m_parent->GetShader(); }

private:
    std::shared_ptr<Material> m_parent;

    std::unordered_map<std::string, glm::vec3> m_vec3s;
    std::unordered_map<std::string, glm::vec4> m_vec4s;

    struct TextureBinding {
        std::shared_ptr<Texture2D> Texture;
        std::uint32_t Slot;
    };
    std::unordered_map<std::string, TextureBinding> m_textures;
    std::uint32_t m_nextTextureSlot = 0;
};

} // namespace zui