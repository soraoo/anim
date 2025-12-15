#pragma once

#include "../glad/glad.h"
#include <GLFW/glfw3.h>

namespace engine {
class App {
public:
    App();
    ~App();
    App(const App&) = delete;
    App(App&&) = delete;

    App& operator=(const App&) = delete;
    App& operator=(App&&) = delete;

    void run();

private:
    [[nodiscard]] bool init();
    void handle_events();
    void update(float dt);
    void render(float aspect_ratio);
    void clean();

    bool _is_running;
    GLFWwindow* _window;
};
} // namespace engine
