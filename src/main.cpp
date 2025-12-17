#include "app/app.h"
#include "scene/test_scene.h"

int main() {
    App app;
    app.run(new TestScene());
    return 0;
}
