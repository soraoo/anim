#include "test_scene.h"

#include <spdlog/spdlog.h>

void TestScene::on_enter() {
    spdlog::info("enter test scene.");
}

void TestScene::on_exit() {
    spdlog::info("exit test scene.");
}
