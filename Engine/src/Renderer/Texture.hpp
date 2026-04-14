#pragma once
#include "../Core/API.hpp"
#include <memory>
#include <string>
#include <cstdint>

namespace zui {

class ZUI_API Texture {
public:
    virtual ~Texture() = default;
    virtual int GetWidth() const = 0;
    virtual int GetHeight() const = 0;
    virtual std::uint32_t GetID() const = 0;
    virtual void Bind(std::uint32_t slot = 0) const = 0;
    virtual bool operator==(const Texture& other) const = 0;
};

class ZUI_API Texture2D : public Texture {
public:
    static std::shared_ptr<Texture2D> Create(const std::string& path);
    static std::shared_ptr<Texture2D> Create(int width, int height);
};

} // namespace zui