#pragma once

#include "scene.h"

class TestScene final : public SceneBase {
public:
    void on_enter() override;
    void on_exit() override;
};
