#ifndef KMINTFRAMEWORK_SPACESHIP_H
#define KMINTFRAMEWORK_SPACESHIP_H

#include "cube.h"
#include "board.h"

namespace linalg {
    class spaceship : public cube {
    private:

        void init_matrix(point origin, double width, double height) {
            std::vector<point> points;
            points.emplace_back(point{origin.x()-height/2, origin.y()-width/2, origin.z() - height/2});
            points.emplace_back(point{origin.x()-height/2, origin.y()+width/2, origin.z() - height/2});
            points.emplace_back(point{origin.x()+height/2, origin.y()+width/2, origin.z() - height/2});
            points.emplace_back(point{origin.x()+height/2, origin.y()-width/2, origin.z() - height/2});
            points.emplace_back(point{origin.x()-height/2, origin.y()-width/2, origin.z() + height/2});
            points.emplace_back(point{origin.x()-height/2, origin.y()+width/2, origin.z() + height/2});
            points.emplace_back(point{origin.x()+height/2, origin.y()+width/2, origin.z() + height/2});
            points.emplace_back(point{origin.x()+height/2, origin.y()-width/2, origin.z() + height/2});
            points.push_back(origin);

            points.emplace_back(point { origin.x() + _width/2, origin.y(), origin.z()}); //local x-axis
            points.emplace_back(point { origin.x(), origin.y() + _width/2, origin.z()}); //local y-axis
            points.emplace_back(point { origin.x(), origin.y(), origin.z() + -_width/2}); //local z-axis

            _m = matrix(3, 12, points);
        }
    public:
        spaceship(point origin, double width, double height, board* board) : cube{origin, width, board} {
            init_matrix(origin, width, height);
        }

        void update(double dt) override {
            if(!_is_alive)
                return;
            update_mutation();
            do_mutation();
            init_mutation_matrix();
        }

        void shoot(){
            point x_axis = get_x_axis();
            point origin = get_origin();
            point vector = x_axis - origin;

            point move = get_x_axis() - get_origin();

            _board->add_cube(new cube(x_axis, 0.5, vector.x()*0.01 + move.x()*_move_speed, vector.y()*0.01+move.y()*_move_speed, vector.z()*0.01 + move.z()*_move_speed, _board));
        }

        void update_mutation() override{
            if(_move.x() != 0 || _move.y() != 0 || _move.z() != 0){
                point move = get_x_axis() - get_origin();
                _move = {move.x()*_move_speed, move.y()*_move_speed, move.z()*_move_speed};
                move_x_y_z(_move.x(), _move.y(), _move.z());
            }
            if(rotate_x_value != 0)
                rotate_x(rotate_x_value);
            if(rotate_y_value != 0)
                rotate_y(rotate_y_value);
            if(rotate_z_value != 0)
                rotate_z(rotate_z_value);
        }

        void handle_events(SDL_Event &event){
            bool button_pressed = event.key.type == SDL_KEYDOWN;

            switch (event.key.keysym.scancode){
                case SDL_SCANCODE_Z :
                    if(button_pressed){
                        _move.z(0.01);
                    }
                    else{
                        _move.z(0);
                    }
                    break;
                case SDL_SCANCODE_X :
                    if(button_pressed){
                        _move.z(-0.01);
                    }
                    else{
                        _move.z(0);
                    }
                    break;
                case SDL_SCANCODE_Q :
                    if(button_pressed){
                        rotate_x_value = -0.01;
                    }
                    else{
                        rotate_x_value = 0;
                    }
                    break;
                case SDL_SCANCODE_E :
                    if(button_pressed){
                        rotate_x_value = 0.01;
                    }
                    else{
                        rotate_x_value = 0;
                    }
                    break;
                case SDL_SCANCODE_A :
                    if(button_pressed){
                        rotate_y_value = -0.01;
                    }
                    else{
                        rotate_y_value = 0;
                    }
                    break;
                case SDL_SCANCODE_D :
                    if(button_pressed){
                        rotate_y_value = 0.01;
                    }
                    else{
                        rotate_y_value = 0;
                    }
                    break;
                case SDL_SCANCODE_W :
                    if(button_pressed){
                        rotate_z_value = 0.01;
                    }
                    else{
                        rotate_z_value = 0;
                    }
                    break;
                case SDL_SCANCODE_S :
                    if(button_pressed){
                        rotate_z_value = -0.01;
                    }
                    else{
                        rotate_z_value = 0;
                    }
                    break;
                case SDL_SCANCODE_LSHIFT :
                    if(button_pressed){
                        point move = get_x_axis() - get_origin();
                        _move = {move.x()*0.1, move.y()*0.1, move.z()*0.1};
                        _move_speed = 0.1;
                    }
                    else{
                        _move = {0,0,0};
                    }
                    break;
                case SDL_SCANCODE_H:
                    if(button_pressed){
                        if(!_draw_help_line){
                            _draw_help_line = true;
                        }
                        else{
                            _draw_help_line = false;
                        }
                    }
                    break;
                case SDL_SCANCODE_SPACE:
                    if(button_pressed){
                        shoot();
                    }
                default:
                    break;
            }
        }
    };
}

#endif //KMINTFRAMEWORK_SPACESHIP_H
