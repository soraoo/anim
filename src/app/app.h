#pragma once

#include <SDL3/SDL_video.h>

class App final {
public:
    App();
    ~App();
    explicit App(const App&) = delete;
    explicit App(App&&) = delete;

    App& operator=(const App&) = delete;
    App& operator=(App&&) = delete;

    void run();

private:
    [[nodiscard]] bool init();
    [[nodiscard]] bool init_log();
    [[nodiscard]] bool init_sdl();
    [[nodiscard]] bool init_gl();

    void handle_events();
    void update(float dt);
    void render();
    void clean();

    bool _is_running;
    SDL_Window* _window;
    SDL_GLContext _gl_context;
};
