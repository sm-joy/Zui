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

void OpenglRendererAPI::DrawIndexed(const std::shared_ptr<VertexArray>& va, std::uint32_t indexCount) {
    if (!va || !va->GetIndexBuffer()) {
        return;
    }

    const std::uint32_t count = indexCount ? indexCount : va->GetIndexBuffer()->GetCount();
    glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
}

void OpenglRendererAPI::DrawArrays(const std::shared_ptr<VertexArray>& va, std::uint32_t vertexCount) {
    if (!va || vertexCount == 0) {
        return;
    }

    glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(vertexCount));
}

} // namespace zui
