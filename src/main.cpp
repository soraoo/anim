#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>
#include "glad/glad.h"

int main() {
    spdlog::info("Hello, world.");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,
                        SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    SDL_Window* _window = SDL_CreateWindow(
        "anim", 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!_window) {
        return 1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(_window);
    if (!gl_context) {
        return 1;
    }

    SDL_GL_SetSwapInterval(1);

    if (!gladLoadGLLoader(
            reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress))) {
        return 1;
    }

    bool _is_running = true;
    while (_is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EventType::SDL_EVENT_QUIT) {
                _is_running = false;
            }
        }

        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(_window);
    }

    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(_window);
    SDL_Quit();

    return 0;
}
