#pragma once

#include <memory>

#include <SDL3/SDL_events.h>

class SceneBase {
public:
    virtual ~SceneBase() = default;

    virtual void on_enter() {}
    virtual void on_handle_events(const SDL_Event&) {}
    virtual void on_update(float) {}
    virtual void on_render() {}
    virtual void on_exit() {}
};

class SceneHandler final {
public:
    SceneHandler() = default;
    ~SceneHandler() = default;
    SceneHandler(const SceneHandler&) = delete;
    SceneHandler(SceneHandler&&) = delete;

    SceneHandler& operator=(const SceneHandler&) = delete;
    SceneHandler& operator=(SceneHandler&&) = delete;

    void switch_scene(SceneBase* new_scene);

    void handle_events(const SDL_Event& event);
    void update(float dt);
    void render();
    void clean();

private:
    std::unique_ptr<SceneBase> _cur_scene;
};
