#pragma once

#include <memory>

#include <SDL3/SDL_video.h>

#include "../scene/scene.h"

class App final {
public:
    App();
    ~App();
    explicit App(const App&) = delete;
    explicit App(App&&) = delete;

    App& operator=(const App&) = delete;
    App& operator=(App&&) = delete;

    void run(SceneBase* start_scene);

private:
    [[nodiscard]] bool init();
    [[nodiscard]] bool init_log();
    [[nodiscard]] bool init_sdl();
    [[nodiscard]] bool init_gl();
    [[nodiscard]] bool init_handlers();

    void handle_events();
    void update(float dt);
    void render();
    void clean();

    bool _is_running;
    SDL_Window* _window;
    SDL_GLContext _gl_context;

    std::unique_ptr<SceneHandler> _scene_handler;
};
