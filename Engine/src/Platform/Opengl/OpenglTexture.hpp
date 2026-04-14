#pragma once
#include "../../Renderer/Texture.hpp"

#include <cstdint>
#include <string>

namespace zui {

class OpenglTexture2D : public Texture2D {
public:
    OpenglTexture2D(const std::string& filepath);
    OpenglTexture2D(int width, int height);
    ~OpenglTexture2D() override;

    int GetWidth() const override { return m_width; }
    int GetHeight() const override { return m_height; }
    std::uint32_t GetID() const override { return m_id; }

    void Bind(uint32_t slot = 0) const override;
    void SetData(void* data, std::uint32_t size);

    bool operator==(const Texture& other) const override {
        const OpenglTexture2D& tex = static_cast<const OpenglTexture2D&>(other);
        if (m_id > 0 && tex.m_id > 0) {
            return m_id == tex.m_id;
        }
        return false;
    }

private:
    std::string m_path;
    std::uint32_t m_id = 0;
    int m_width = 0;
    int m_height = 0;

    int m_internalFormat, m_dataFormat;
};

} // namespace zui