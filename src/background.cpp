#include "background.h"
#include "renderer.h"

namespace linalg {

    void background::draw(renderer &renderer, camera cam) {
        renderer.draw_image({640.0, 360.0}, _i);
    }
}
