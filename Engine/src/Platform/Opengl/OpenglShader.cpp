#include "OpenglShader.hpp"

#include "../../Logger/Log.hpp"
#include "glad/gl.h"

#include <memory>

namespace zui {

static GLenum ShaderStageTypeToGLenum(ShaderStageType type) {
    switch (type) {
    case ShaderStageType::VERTEX:
        return GL_VERTEX_SHADER;
    case ShaderStageType::FRAGMENT:
        return GL_FRAGMENT_SHADER;
    case ShaderStageType::GEOMETRY:
        return GL_GEOMETRY_SHADER;
    case ShaderStageType::COMPUTE:
        return GL_COMPUTE_SHADER;
    case ShaderStageType::NONE:
    default:
        LOGGER_ERROR("Unkown Shader Stage Type");
        return 0;
    }
}

static const char* ShaderStageTypeToString(ShaderStageType type) {
    switch (type) {
    case ShaderStageType::VERTEX:
        return "VERTEX_SHADER";
    case ShaderStageType::FRAGMENT:
        return "FRAGMENT_SHADER";
    case ShaderStageType::GEOMETRY:
        return "GEOMETRY_SHADER";
    case ShaderStageType::COMPUTE:
        return "COMPUTE_SHADER";
    case ShaderStageType::NONE:
        return "NONE";
    default:
        LOGGER_ERROR("Unkown Shader Stage Type");
        return "UNKOWN";
    }
}

OpenglShaderStage::OpenglShaderStage(ShaderStageType type, const std::string& source) : m_type(type) {
    m_id = glCreateShader(ShaderStageTypeToGLenum(type));
    const char* src = source.c_str();
    glShaderSource(m_id, 1, &src, nullptr);
    glCompileShader(m_id);

    int success = 0;
    glGetShaderiv(m_id, GL_COMPILE_STATUS, &success);
    if (!success) {
        int len = 0;
        glGetShaderiv(m_id, GL_INFO_LOG_LENGTH, &len);
        std::unique_ptr<char[]> msg = std::make_unique<char[]>(len);
        glGetShaderInfoLog(m_id, len, &len, msg.get());

        LOGGER_ERROR("[ShaderStage] {} Compilation Failed! : {}", ShaderStageTypeToString(type), msg.get());

        glDeleteShader(m_id);
        m_id = 0;
        return;
    }

    m_valid = true;
    LOGGER_TRACE("[ShaderStage] {} Compilation Successful (id={})", ShaderStageTypeToString(type), m_id);
}

OpenglShaderStage::~OpenglShaderStage() {
    if (m_id) {
        glDeleteShader(m_id);
        m_id = 0;
    }
}

void OpenglShaderStage::DestroyShaderStage() {
    if (m_id) {
        glDeleteShader(m_id);
        m_id = 0;
        m_valid = false;
    }
}


OpenglShader::OpenglShader(const std::string& name, const std::vector<std::shared_ptr<ShaderStage>>& stages)
: m_name(name) {
    m_id = glCreateProgram();

    for(const std::shared_ptr<ShaderStage>& stage : stages) {
        if (!stage || !stage->IsValid()) {
            LOGGER_ERROR("[Shader] Shader Stage Is Not Valid.");
            glDeleteProgram(m_id);
            m_id = 0;
            return;
        }
        glAttachShader(m_id, stage->GetStageId());
    }

    glLinkProgram(m_id);

    int success = 0;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        int len = 0;
        glGetProgramiv(m_id, GL_INFO_LOG_LENGTH, &len);
        std::unique_ptr<char[]> msg = std::make_unique<char[]>(len);
        glGetProgramInfoLog(m_id, len, &len, msg.get());
        LOGGER_ERROR("[Shader] {} Shader Link Failed! : {}", m_name, msg.get());

        for(const std::shared_ptr<ShaderStage>& stage : stages) {
            glDetachShader(m_id, stage->GetStageId());
        }
        glDeleteProgram(m_id);
        m_id = 0;
        return;
    }

    for(const std::shared_ptr<ShaderStage>& stage : stages) {
        glDetachShader(m_id, stage->GetStageId());
        stage->DestroyShaderStage();
    }

    LOGGER_TRACE("[Shader] '{}' Linked Success! (program={})", name, m_id);
}

OpenglShader::~OpenglShader() {
    if (m_id) {
        glDeleteProgram(m_id);
    }
}

void OpenglShader::Bind()   const { glUseProgram(m_id); }
void OpenglShader::Unbind() const { glUseProgram(0); }


} // namespace zui
