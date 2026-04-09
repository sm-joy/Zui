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
    const std::string& GetName() const override { return m_name; }

private:
    std::uint32_t m_id = 0;
    std::string m_name;
};

} // namespace zui
