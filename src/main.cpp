#include <SDL3/SDL.h>
#include <spdlog/spdlog.h>

int main() {
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* _window = SDL_CreateWindow("anim", 1280, 720, 0);

    spdlog::set_level(spdlog::level::info);
    spdlog::info("Hello, world.");

    auto is_running = true;
    while (is_running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_EventType::SDL_EVENT_QUIT) {
                is_running = false;
            }
        }
    }
    
    SDL_DestroyWindow(_window);
    SDL_Quit();

    return 0;
}
