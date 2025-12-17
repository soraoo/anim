#include "app.h"

#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

#include "../glad/glad.h"

App::App()
    : _is_running{false}, _window{nullptr}, _gl_context{nullptr},
      _scene_handler{nullptr} {}

App::~App() {
    if (_is_running) {
        spdlog::warn("app shutdown exception, clean fallback.");
        clean();
    }
}

void App::run(SceneBase* start_scene) {
    if (!init()) {
        return;
    }

    _scene_handler->switch_scene(start_scene);

    while (_is_running) {
        handle_events();
        update(0.0f);
        render();
    }

    clean();
}

bool App::init() {
    _is_running = true;

    if (!init_log()) {
        return false;
    }

    if (!init_sdl()) {
        return false;
    }

    if (!init_gl()) {
        return false;
    }

    if (!init_handlers()) {
        return false;
    }

    return true;
}

bool App::init_log() {
#ifdef NDEBUG
    spdlog::set_level(spdlog::level::info);
#else
    spdlog::set_level(spdlog::level::trace);
#endif

    return true;
}

bool App::init_sdl() {
    if (!SDL_Init(SDL_INIT_VIDEO)) {
        spdlog::error("sdl init failed: ", SDL_GetError());
        return false;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_Window* _window = SDL_CreateWindow(
        "anim", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!_window) {
        spdlog::error("sdl create window failed: ", SDL_GetError());
        return false;
    }

    _gl_context = SDL_GL_CreateContext(_window);
    if (!_gl_context) {
        spdlog::error("sdl create gl context failed: ", SDL_GetError());
        return false;
    }

    if (!SDL_GL_SetSwapInterval(1)) {
        spdlog::error("sdl set vsync failed: ", SDL_GetError());
        return false;
    }

    return true;
}

bool App::init_gl() {
    return gladLoadGLLoader(
        reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress));
}

bool App::init_handlers() {
    _scene_handler = std::make_unique<SceneHandler>();

    return true;
}

void App::handle_events() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_EventType::SDL_EVENT_QUIT) {
            _is_running = false;
        }
    }

    _scene_handler->handle_events(event);
}

void App::update(float dt) { _scene_handler->update(dt); }

void App::render() {
    _scene_handler->render();

    SDL_GL_SwapWindow(_window);
}

void App::clean() {
    _scene_handler->clean();

    if (_gl_context) {
        SDL_GL_DestroyContext(_gl_context);
        _gl_context = nullptr;
    }

    if (_window) {
        SDL_DestroyWindow(_window);
        _window = nullptr;
    }

    SDL_Quit();
    _is_running = false;
}
