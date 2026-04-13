#pragma once
#include "../Core/API.hpp"
#include "../Values/Color.hpp"

#include <cstdint>
#include <glm/glm.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>
#include <type_traits>

namespace zui {

template <typename>
inline constexpr bool ALWAYS_FALSE_V = false;

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

    virtual void SetInt(const std::string& name, int value) const = 0;
    virtual void SetIntArray(const std::string& name, int* value, int count) const = 0;
    virtual void SetFloat(const std::string& name, float value) const = 0;
    virtual void SetDouble(const std::string& name, double value) const = 0;
    virtual void SetFloat2(const std::string& name, const glm::vec2& value) const = 0;
    virtual void SetFloat3(const std::string& name, const glm::vec3& value) const = 0;
    virtual void SetFloat4(const std::string& name, const glm::vec4& value) const = 0;
    virtual void SetMat2(const std::string& name, const glm::mat2& value) const = 0;
    virtual void SetMat3(const std::string& name, const glm::mat3& value) const = 0;
    virtual void SetMat4(const std::string& name, const glm::mat4& value) const = 0;

    template <typename T> void Set(const std::string& name, T const& value) {
        if constexpr (std::is_same_v<T, float>) {
            SetFloat(name, value);
        } else if constexpr (std::is_same_v<T, double>) {
            SetDouble(name, value);
        } else if constexpr (std::is_same_v<T, int>) {
            SetInt(name, value);
        } else if constexpr (std::is_same_v<T, bool>) {
            SetInt(name, value ? 1 : 0);
        } else if constexpr (std::is_same_v<T, glm::vec2>) {
            SetFloat2(name, value);
        } else if constexpr (std::is_same_v<T, glm::vec3>) {
            SetFloat3(name, value);
        } else if constexpr (std::is_same_v<T, glm::vec4>) {
            SetFloat4(name, value);
        } else if constexpr (std::is_same_v<T, glm::mat2>) {
            SetMat2(name, value);
        } else if constexpr (std::is_same_v<T, glm::mat3>) {
            SetMat3(name, value);
        } else if constexpr (std::is_same_v<T, glm::mat4>) {
            SetMat4(name, value);
        } else if constexpr (std::is_same_v<T, Color>) {
            glm::vec4 vcolor = {value.R, value.G, value.B, value.A};
            SetFloat4(name, vcolor);
        } else {
            static_assert(ALWAYS_FALSE_V<T>, "Unsupported type passed to Shader::setUniform");
        }
    }

    template <typename TargetType, typename ValueType> void Set(const std::string& name, ValueType const& value) {
        TargetType valueT = static_cast<TargetType>(value);
        Set(name, valueT);
    }

    virtual const std::string& GetName() const = 0;

    static std::shared_ptr<Shader> Create(const std::string& name,
                                          const std::vector<std::shared_ptr<ShaderStage>>& stages);
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
