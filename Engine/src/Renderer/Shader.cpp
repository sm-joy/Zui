#include "Shader.hpp"

#include "../Logger/Log.hpp"
#include "../Platform/Opengl/OpenglShader.hpp"
#include "../Renderer/Renderer.hpp"

#include <cstring>
#include <fstream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

namespace zui {

static std::string ReadFile(const std::string& filepath) {
    std::ifstream file(filepath, std::ios::in | std::ios::binary);
    if (!file) {
        LOGGER_ERROR("Cannot Open Shader File: {}", filepath);
        return "";
    }
    std::stringstream ss;
    ss << file.rdbuf();
    return ss.str();
}

static std::string ParseNameFromPath(const std::string& filepath) {
    auto slash = filepath.find_last_of("/\\");
    slash = (slash == std::string::npos) ? 0 : slash + 1;
    auto dot = filepath.rfind('.');
    auto len = (dot == std::string::npos) ? filepath.size() - slash : dot - slash;
    return filepath.substr(slash, len);
}

static std::string Trim(const std::string& value) {
    const std::size_t first = value.find_first_not_of(" \t");
    if (first == std::string::npos) {
        return "";
    }

    const std::size_t last = value.find_last_not_of(" \t");
    return value.substr(first, last - first + 1);
}

static std::unordered_map<ShaderStageType, std::string> ParseStages(const std::string& src) {
    static std::unordered_map<std::string, ShaderStageType> stageMap = {
        {"vertext", ShaderStageType::VERTEX},
        {"fragment", ShaderStageType::FRAGMENT},
        {"geometry", ShaderStageType::GEOMETRY},
        {"compute", ShaderStageType::COMPUTE},
    };

    std::unordered_map<ShaderStageType, std::string> out;
    const char* tok = "#type";
    size_t pos = src.find(tok);

    while (pos != std::string::npos) {
        size_t eol = src.find_first_of("\r\n", pos);

        if (eol == std::string::npos) {
            LOGGER_ERROR("[Shader Stage] Syntax error after #type");
            break;
        }

        std::string key = Trim(src.substr(pos + std::strlen(tok) + 1, eol - (pos + std::strlen(tok) + 1)));

        auto it = stageMap.find(key);
        if (it == stageMap.end()) {
            LOGGER_ERROR("[Shader Stage] Unknown stage tag: #type {}", key);
            break;
        }

        size_t next = src.find_first_not_of("\r\n", eol);
        if (next == std::string::npos) {
            LOGGER_ERROR("[Shader Stage] Missing stage source for {}", key);
            break;
        }

        pos = src.find(tok, next);

        out[it->second] = (pos == std::string::npos) ? src.substr(next) : src.substr(next, pos - next);
    }
    return out;
}

std::shared_ptr<ShaderStage> ShaderStage::CreateFromFile(ShaderStageType type, const std::string& filepath) {
    return CreateFromSource(type, ReadFile(filepath));
}

std::shared_ptr<ShaderStage> ShaderStage::CreateFromSource(ShaderStageType type, const std::string& source) {
    switch (Renderer::GetAPI()) {
    case GraphicsAPI::OPENGL:
        return std::make_shared<OpenglShaderStage>(type, source);
    default: {
        LOGGER_ERROR("Unknown RendererAPI");
        return nullptr;
    }
    }
}

std::shared_ptr<Shader> Shader::Create(const std::string& name,
                                       const std::vector<std::shared_ptr<ShaderStage>>& stages) {
    switch (Renderer::GetAPI()) {
    case GraphicsAPI::OPENGL: {
        return std::make_shared<OpenglShader>(name, stages);
    }
    default: {
        LOGGER_ERROR("Unknown RendererAPI");
        return nullptr;
    }
    }
}

std::shared_ptr<Shader> Shader::CreateFromFile(const std::string& filepath) {
    return CreateFromFile(ParseNameFromPath(filepath), filepath);
}

std::shared_ptr<Shader> Shader::CreateFromFile(const std::string& name, const std::string& filepath) {
    std::unordered_map<ShaderStageType, std::string> stageSources = ParseStages(ReadFile(filepath));
    if (stageSources.empty()) {
        LOGGER_ERROR("[Shader] No shader stages found in '{}'.", filepath);
        return nullptr;
    }

    std::vector<std::shared_ptr<ShaderStage>> stages;
    stages.reserve(stageSources.size());

    for (const auto& pair : stageSources) {
        std::shared_ptr<ShaderStage> stage = ShaderStage::CreateFromSource(pair.first, pair.second);
        if (!stage || !stage->IsValid()) {
            LOGGER_ERROR("[Shader] Failed to create shader stage for '{}'.", filepath);
            return nullptr;
        }

        stages.push_back(stage);
    }
    return Create(name, stages);
}

void ShaderLibrary::Add(const std::shared_ptr<Shader>& shader) {
    if (!shader) {
        LOGGER_ERROR("[Shader Library] Cannot add null shader.");
        return;
    }

    m_shaders[shader->GetName()] = shader;
}

void ShaderLibrary::Add(const std::string& name, const std::shared_ptr<Shader>& shader) {
    if (!shader) {
        LOGGER_ERROR("[Shader Library] Cannot add null shader '{}'.", name);
        return;
    }

    m_shaders[name] = shader;
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& filepath) {
    std::shared_ptr<Shader> shader = Shader::CreateFromFile(filepath);
    Add(shader);
    return shader;
}

std::shared_ptr<Shader> ShaderLibrary::Load(const std::string& name, const std::string& filepath) {
    std::shared_ptr<Shader> shader = Shader::CreateFromFile(name, filepath);
    Add(name, shader);
    return shader;
}

std::shared_ptr<Shader> ShaderLibrary::Get(const std::string& name) const {
    auto it = m_shaders.find(name);
    if (it == m_shaders.end()) {
        LOGGER_ERROR("[Shader Library] '{}' key not found!", name);
        return nullptr;
    }

    return it->second;
}

bool ShaderLibrary::Exists(const std::string& name) const {
    return m_shaders.count(name) > 0;
}

} // namespace zui
