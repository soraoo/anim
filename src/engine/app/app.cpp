#include "app.h"

#include <spdlog/spdlog.h>

namespace engine {
App::App() : _is_running(false), _window(nullptr) {}

App::~App() {
    if (_is_running) {
        clean();
    }
}

void App::run() {
    if (!init()) {
        spdlog::error("app init failed.");
        return;
    }

    while (!glfwWindowShouldClose(_window)) {
        handle_events();
        update(0.0f);
        render(0.0f);
    }

    clean();
}

bool App::init() {
    _is_running = true;

#ifdef NDEBUG
    spdlog::set_level(spdlog::level::info);
#else
    spdlog::set_level(spdlog::level::trace);
#endif

    if (!glfwInit()) {
        spdlog::error("glfw init failed: ", glfwGetError(nullptr));
        return false;
    }

    _window = glfwCreateWindow(1280, 720, "anim", nullptr, nullptr);
    if (!_window) {
        spdlog::error("glfw create window failed: ", glfwGetError(nullptr));
        return false;
    }

    glfwMakeContextCurrent(_window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        spdlog::error("glad load gl failed.");
        return false;
    }

    return true;
}

void App::handle_events() {
    glfwPollEvents();
}

void App::update(float) {}

void App::render(float) { glfwSwapBuffers(_window); }

void App::clean() {
    if (_window) {
        glfwDestroyWindow(_window);
    }

    glfwTerminate();

    _is_running = false;
}
} // namespace engine
