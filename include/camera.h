#ifndef KMINTFRAMEWORK_CAMERA_H
#define KMINTFRAMEWORK_CAMERA_H

#include <cmath>
#include <SDL_events.h>
#include "point.h"

namespace linalg {
    class matrix;
    class camera {
    private:
        point _eye { 0, 0, 100, 1};
        point _lookAt { 0, 0, 0, 1};
        point _up { 0, 1, 0, 1};
        double _near = 2;
        double _far = 100;
        double _field_of_view = M_PI/4;
        const double _screen_size = 720;
        point _move;
    public:
        explicit camera();
        matrix create_camera_matrix();
        matrix create_projection_matrix();
        point correct_vector(point a);
        void turn_camera(double amount);
        void update();
        void update_position();
        void handle_event(SDL_Event &event);
    };
}

#endif //KMINTFRAMEWORK_CAMERA_H
