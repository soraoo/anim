#include "scene.h"

void SceneHandler::switch_scene(SceneBase* new_scene) {
    if (_cur_scene) {
        _cur_scene->on_exit();
    }
    _cur_scene.reset(new_scene);
    _cur_scene->on_enter();
}

void SceneHandler::handle_events(const SDL_Event& event) {
    if (_cur_scene) {
        _cur_scene->on_handle_events(event);
    }
}

void SceneHandler::update(float dt) {
    if (_cur_scene) {
        _cur_scene->on_update(dt);
    }
}

void SceneHandler::render() {
    if (_cur_scene) {
        _cur_scene->on_render();
    }
}

void SceneHandler::clean() {
    if (_cur_scene) {
        _cur_scene->on_exit();
        _cur_scene = nullptr;
    }
}
