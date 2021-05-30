#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>
#include <string_view>
#include <glm/vec2.hpp>

// #include "EventProvider.hpp"

namespace kawe {

class EventProvider;

class Window {
public:
    Window(
        EventProvider &,
        const std::string_view window_title,
        glm::ivec2 &&size,
        glm::ivec2 &&position = {0, 0},
        bool isFullscreen = false);

    ~Window() { glfwDestroyWindow(window); }

    auto get() const noexcept -> GLFWwindow * { return window; }

    auto should_close() -> bool { return m_should_close; }

    void close()
    {
        m_should_close = true;
        glfwSetWindowShouldClose(window, true);
    }

    // note : send the event to imgui
    template<typename T>
    auto useEvent(const T &) -> void;

    template<typename T = double>
    [[nodiscard]] auto getSize() const noexcept -> glm::vec<2, T>
    {
        int width{};
        int height{};
        ::glfwGetWindowSize(window, &width, &height);
        return {static_cast<T>(width), static_cast<T>(height)};
    }

    template<typename T = double>
    [[nodiscard]] auto getAspectRatio() const noexcept -> T
    {
        const auto size = getSize<T>();
        return static_cast<T>(size.x) / static_cast<T>(size.y);
    }

private:
    GLFWwindow *window;

    bool isWindowIconofied;
    bool isWindowFocused;
    bool m_should_close;
};

} // namespace kawe