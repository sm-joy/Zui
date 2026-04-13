#pragma once
#include "../../Renderer/Shader.hpp"
#include <glad/gl.h>
#include <memory>
#include <string>
#include <vector>

namespace zui {

class OpenglShaderStage : public ShaderStage {
public:
    OpenglShaderStage(ShaderStageType type, const std::string& source);
    ~OpenglShaderStage() override;

    ShaderStageType GetStageType() const override { return m_type; }
    bool IsValid() const override { return m_valid; }
    std::uint32_t GetStageId() const override { return m_id; }
    void DestroyShaderStage() override;
private:
    std::uint32_t m_id = 0;
    ShaderStageType m_type = ShaderStageType::NONE;
    bool m_valid = false;
};



class OpenglShader : public Shader {
public:
    OpenglShader(const std::string& name, const std::vector<std::shared_ptr<ShaderStage>>& stages);
    ~OpenglShader() override;

    void Bind()   const override;
    void Unbind() const override;
    void SetInt(const std::string& name, int value) const override;
    void SetIntArray(const std::string& name, int* value, int count) const override;
    void SetFloat(const std::string& name, float value) const override;
    void SetDouble(const std::string& name, double value) const override;
    void SetFloat2(const std::string& name, const glm::vec2& value) const override;
    void SetFloat3(const std::string& name, const glm::vec3& value) const override;
    void SetFloat4(const std::string& name, const glm::vec4& value) const override;
    void SetMat2(const std::string& name, const glm::mat2& value) const override;
    void SetMat3(const std::string& name, const glm::mat3& value) const override;
    void SetMat4(const std::string& name, const glm::mat4& value) const override;
    const std::string& GetName() const override { return m_name; }

private:
    std::uint32_t m_id = 0;
    std::string m_name;

    int LocateUniform(const std::string& name) const;
};

} // namespace zui
