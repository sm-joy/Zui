#include "OpenglTexture.hpp"

#include "../../Logger/Log.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include <glad/gl.h>
#include <glm/glm.hpp>
#include <stb_image.h>

namespace zui {

OpenglTexture2D::OpenglTexture2D(const std::string& filepath) : m_path(filepath) {
    int w, h, c;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filepath.c_str(), &w, &h, &c, 0);
    if (!data) {
        LOGGER_ERROR("Failed to load texture at filepath: {}", filepath);
        return;
    }

    m_width = w;
    m_height = h;
    if (c == 4) {
        m_internalFormat = GL_RGBA8;
        m_dataFormat = GL_RGBA;
    } else {
        m_internalFormat = GL_RGB8;
        m_dataFormat = GL_RGB;
    }

    int mipLevels = 1 + static_cast<int>(glm::floor(glm::log2(static_cast<float>(glm::max(m_width, m_height)))));

    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
    glTextureStorage2D(m_id, mipLevels, m_internalFormat, m_width, m_height);

    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTextureParameteri(m_id, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
    glGenerateTextureMipmap(m_id);

    stbi_image_free(data);
}

OpenglTexture2D::OpenglTexture2D(int w, int h)
    : m_width(w), m_height(h), m_internalFormat(GL_RGBA8), m_dataFormat(GL_RGBA) {
    glCreateTextures(GL_TEXTURE_2D, 1, &m_id);
    glTextureStorage2D(m_id, 1, m_internalFormat, w, h);
    glTextureParameteri(m_id, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTextureParameteri(m_id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}
OpenglTexture2D::~OpenglTexture2D() {
    if (m_id > 0) {
        glDeleteTextures(1, &m_id);
    }
}

void OpenglTexture2D::SetData(void* data, std::uint32_t size) {
    std::uint32_t bpp = (m_dataFormat == GL_RGBA) ? 4 : 3;
    if (size != m_width * m_height * bpp) {
        LOGGER_ERROR("Data must fill the entire texture.");
        return;
    }
    glTextureSubImage2D(m_id, 0, 0, 0, m_width, m_height, m_dataFormat, GL_UNSIGNED_BYTE, data);
}

void OpenglTexture2D::Bind(std::uint32_t slot) const {
    glBindTextureUnit(slot, m_id);
}

} // namespace zui