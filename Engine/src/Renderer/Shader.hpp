#pragma once
#include "../Core/API.hpp"

#include <cstdint>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>


namespace zui {

enum class ShaderStageType : std::uint8_t { NONE, VERTEX, FRAGMENT, GEOMETRY, COMPUTE, COUNT };


class ZUI_API ShaderStage {
public:
    virtual ~ShaderStage() = default;

    virtual ShaderStageType GetStageType() const = 0;
    virtual bool IsValid() const = 0;
    virtual std::uint32_t GetStageId() const = 0;
    virtual void DestroyShaderStage() = 0;

    static std::shared_ptr<ShaderStage> CreateFromFile(ShaderStageType type, const std::string& filepath);
    static std::shared_ptr<ShaderStage> CreateFromSource(ShaderStageType type, const std::string& source);
};


class ZUI_API Shader {
public:
    virtual ~Shader() = default;

    virtual void Bind() const = 0;
    virtual void Unbind() const = 0;

    virtual const std::string& GetName() const = 0;

    static std::shared_ptr<Shader> Create(const std::string& name, const std::vector<std::shared_ptr<ShaderStage>>& stages);
    static std::shared_ptr<Shader> CreateFromFile(const std::string& filepath);
    static std::shared_ptr<Shader> CreateFromFile(const std::string& name, const std::string& filepath);
};

class ZUI_API ShaderLibrary {
public:
    void Add(const std::shared_ptr<Shader>& shader);
    void Add(const std::string& name, const std::shared_ptr<Shader>& shader);

    std::shared_ptr<Shader> Load(const std::string& filepath);
    std::shared_ptr<Shader> Load(const std::string& name, const std::string& filepath);

    std::shared_ptr<Shader> Get(const std::string& name) const;
    bool Exists(const std::string& name) const;

private:
    std::unordered_map<std::string, std::shared_ptr<Shader>> m_shaders;
};

} // namespace zui
