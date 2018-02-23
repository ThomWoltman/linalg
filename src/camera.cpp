#include <vector>
#include <iostream>
#include "camera.h"
#include "matrix.h"

namespace linalg {
    camera::camera() {

    }

    matrix camera::create_camera_matrix() {
        point vector_z = normalize(_eye - _lookAt);
        point vector_y = normalize(_up);
        point vector_x = normalize(cross_product(vector_y, vector_z));
        vector_y = normalize(cross_product(vector_z, vector_x));

        point a { vector_x.x(), vector_y.x(), vector_z.x(), 0};
        point b { vector_x.y(), vector_y.y(), vector_z.y(), 0};
        point c { vector_x.z(), vector_y.z(), vector_z.z(), 0};
        point d { -dot(vector_x, _eye), -dot(vector_y, _eye), -dot(vector_z, _eye), 1 };

        std::vector<point> points;
        points.push_back(a);
        points.push_back(b);
        points.push_back(c);
        points.push_back(d);

        return matrix { 4, 4, points };
    }

    matrix camera::create_projection_matrix() {
        double abc = tan(_field_of_view/2);
        double scale = _near * abc;

        point a { scale, 0, 0, 0 };
        point b { 0, scale, 0, 0 };
        point c { 0, 0, (-_far) / (_far - _near), -1 };
        point d { 0, 0, (-_far*_near) / (_far-_near), 0 };

        std::vector<point> points;
        points.push_back(a);
        points.push_back(b);
        points.push_back(c);
        points.push_back(d);

        return matrix { 4, 4, points};
    }

    point camera::correct_vector(point a) {
        a.x( _screen_size/2+(a.x()+1) / a.w() * 1280 * 0.5 );
        a.y( _screen_size/2+(a.y()+1) / a.w() * 1280 * 0.5 );
        a.z(-a.z());

        return a;
    }

    void camera::update() {
        update_position();
    }

    void camera::update_position() {
        if(_move.x() != 0 || _move.y() != 0 || _move.z() != 0){
            _eye = _eye + _move;
            _lookAt = _lookAt + _move;
        }
    }

    void camera::handle_event(SDL_Event &event) {
        bool button_pressed = event.key.type == SDL_KEYDOWN;

        switch (event.key.keysym.scancode){
            case SDL_SCANCODE_UP :
                if(button_pressed){
                    _move.y(0.1);
                }
                else{
                    _move.y(0);
                }
                break;
            case SDL_SCANCODE_DOWN :
                if(button_pressed){
                    _move.y(-0.1);
                }
                else{
                    _move.y(0);
                }
                break;
            case SDL_SCANCODE_LEFT :
                if(button_pressed){
                    _move.x(-0.1);
                }
                else{
                    _move.x(0);
                }
                break;
            case SDL_SCANCODE_RIGHT :
                if(button_pressed){
                    _move.x(0.1);
                }
                else{
                    _move.x(0);
                }
                break;
            case SDL_SCANCODE_PAGEUP :
                if(button_pressed){
                    _move.z(0.1);
                }
                else{
                    _move.z(0);
                }
                break;
            case SDL_SCANCODE_PAGEDOWN :
                if(button_pressed){
                    _move.z(-0.1);
                }
                else{
                    _move.z(0);
                }
                break;
            default:
                break;
        }
    }
}