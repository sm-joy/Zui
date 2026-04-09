#pragma once

#include "../Logger/Log.hpp"

#include <cstdint>

namespace zui {

enum class ShaderDataBaseType : std::uint8_t { NONE, FLOAT, INT, BOOL, COUNT };

enum class ShaderDataType : std::uint8_t {
    NONE = 0,
    FLOAT,
    FLOAT2,
    FLOAT3,
    FLOAT4,
    INT,
    INT2,
    INT3,
    INT4,
    MAT3,
    MAT4,
    BOOL,
    COUNT
};

struct ShaderDataTypeInfo {
    std::uint32_t Size;
    std::uint32_t ComponentCount;
    std::uint32_t ColumnCount;
    std::uint32_t RowCount;

    ShaderDataBaseType BaseType;

    const char* Name;
};

inline static constexpr ShaderDataTypeInfo SHADER_DATA_TYPE_INFOS[] = {
    /* None   */ {0, 0, 0, 0, ShaderDataBaseType::NONE, "None"},
    /* Float  */ {4 * 1, 1, 1, 1, ShaderDataBaseType::FLOAT, "Float"},
    /* Float2 */ {4 * 2, 2, 1, 2, ShaderDataBaseType::FLOAT, "Float2"},
    /* Float3 */ {4 * 3, 3, 1, 3, ShaderDataBaseType::FLOAT, "Float3"},
    /* Float4 */ {4 * 4, 4, 1, 4, ShaderDataBaseType::FLOAT, "Float4"},
    /* Int    */ {4 * 1, 1, 1, 1, ShaderDataBaseType::INT, "Int"},
    /* Int2   */ {4 * 2, 2, 1, 2, ShaderDataBaseType::INT, "Int2"},
    /* Int3   */ {4 * 3, 3, 1, 3, ShaderDataBaseType::INT, "Int3"},
    /* Int4   */ {4 * 4, 4, 1, 4, ShaderDataBaseType::INT, "Int4"},
    /* Mat3   */ {4 * 3 * 3, 9, 3, 3, ShaderDataBaseType::FLOAT, "Mat3"},
    /* Mat4   */ {4 * 4 * 4, 16, 4, 4, ShaderDataBaseType::FLOAT, "Mat4"},
    /* Bool   */ {1, 1, 1, 1, ShaderDataBaseType::BOOL, "Bool"},
};

inline const ShaderDataTypeInfo& GetShaderDataTypeInfo(ShaderDataType type) {
    if (type >= ShaderDataType::COUNT) {
        LOGGER_WARN("Unknown DataType");
        return SHADER_DATA_TYPE_INFOS[0];
    }
    size_t idx = static_cast<size_t>(type);
    return SHADER_DATA_TYPE_INFOS[idx];
}

} // namespace zui