#include "Material.hpp"

#include "Shader.hpp"
#include "Texture.hpp"

#include <memory>

namespace zui {

std::shared_ptr<Material> Material::Create(const std::shared_ptr<Shader>& shader) {
    return std::shared_ptr<Material>(new Material(shader));
}

void Material::SetTexture(const std::string& name, const std::shared_ptr<Texture2D>& tex) {
    auto it = m_textures.find(name);

    if (it == m_textures.end()) {
        m_textures[name] = TextureBinding{.Texture = tex, .Slot = m_nextTextureSlot++};
    } else {
        it->second.Texture = tex;
    }
}

void Material::Bind() const {
    m_shader->Bind();

    for (const auto& [name, value] : m_ints)
        m_shader->SetInt(name, value);
    for (const auto& [name, value] : m_floats)
        m_shader->SetFloat(name, value);
    for (const auto& [name, value] : m_vec2s)
        m_shader->SetFloat2(name, value);
    for (const auto& [name, value] : m_vec3s)
        m_shader->SetFloat3(name, value);
    for (const auto& [name, value] : m_vec4s)
        m_shader->SetFloat4(name, value);
    for (const auto& [name, value] : m_mat2s)
        m_shader->SetMat2(name, value);
    for (const auto& [name, value] : m_mat3s)
        m_shader->SetMat3(name, value);
    for (const auto& [name, value] : m_mat4s)
        m_shader->SetMat4(name, value);

    for (const auto& [name, tb] : m_textures) {
        tb.Texture->Bind(tb.Slot);
        m_shader->SetInt(name, static_cast<int>(tb.Slot));
    }
}

void Material::Unbind() const {
    m_shader->Unbind();
}

std::shared_ptr<MaterialInstance> Material::CreateInstance() {
    return std::make_shared<MaterialInstance>(shared_from_this());
}

void MaterialInstance::SetTexture(const std::string& name, const std::shared_ptr<Texture2D>& tex) {
    auto it = m_textures.find(name);

    if (it == m_textures.end()) {
        m_textures[name] = TextureBinding{.Texture = tex, .Slot = m_nextTextureSlot++};
    } else {
        it->second.Texture = tex;
    }
}

void MaterialInstance::Bind() const {
    m_parent->Bind();

    const auto& shader = m_parent->GetShader();
    for (const auto& [n, v] : m_vec3s)
        shader->SetFloat3(n, v);
    for (const auto& [n, v] : m_vec4s)
        shader->SetFloat4(n, v);
    for (const auto& [n, tb] : m_textures) {
        tb.Texture->Bind(tb.Slot);
        shader->SetInt(n, (int)tb.Slot);
    }
}

void MaterialInstance::Unbind() const {
    m_parent->Unbind();
}

} // namespace zui