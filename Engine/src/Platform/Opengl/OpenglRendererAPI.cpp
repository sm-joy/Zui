#include "OpenglRendererAPI.hpp"

#include <glad/gl.h>
#include <memory>

namespace zui {

void OpenglRendererAPI::Init() {}

void OpenglRendererAPI::SetViewport(int x, int y, int w, int h) {
    glViewport(x, y, w, h);
}

void OpenglRendererAPI::SetClearColor(const Color& c) {
    glClearColor(c.R, c.G, c.B, c.A);
}

void OpenglRendererAPI::Clear() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void OpenglRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& va, std::uint32_t indexCount,
                                    std::uint32_t baseIndex, std::uint32_t baseVertex) {
    if (!va || !va->GetIndexBuffer())
        return;

    const std::uint32_t count = indexCount ? indexCount : va->GetIndexBuffer()->GetCount();
    const void* offset = reinterpret_cast<const void*>(baseIndex * sizeof(std::uint32_t));

    glDrawElementsBaseVertex(GL_TRIANGLES, static_cast<int>(count), GL_UNSIGNED_INT, offset, static_cast<GLint>(baseVertex));
}

void OpenglRendererAPI::DrawArrays(const std::shared_ptr<VertexArray>& va, std::uint32_t vertexCount,
                                   std::uint32_t baseVertex) {
    if (!va || vertexCount == 0)
        return;

    glDrawArrays(GL_TRIANGLES, static_cast<GLint>(baseVertex), static_cast<GLsizei>(vertexCount));
}

} // namespace zui
