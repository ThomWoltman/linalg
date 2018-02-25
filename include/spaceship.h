#ifndef KMINTFRAMEWORK_SPACESHIP_H
#define KMINTFRAMEWORK_SPACESHIP_H

#include "cube.h"
#include "board.h"

namespace linalg {
    class spaceship : public shape {
    private:
        bool _draw_help_line = false;

        void init_mutation_matrix(){
            _mutation = matrix::create_identity_matrix(4);
        }

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

            points.emplace_back(point { origin.x() + width/2, origin.y(), origin.z()}); //local x-axis
            points.emplace_back(point { origin.x(), origin.y() + width/2, origin.z()}); //local y-axis
            points.emplace_back(point { origin.x(), origin.y(), origin.z() + width/2}); //local z-axis

            _m = matrix(3, 12, points);
        }
    public:
        spaceship(point origin, double width, double height, board* board) {
            _board = board;
            init_matrix(origin, width, height);
            init_mutation_matrix();
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

        void draw(renderer &renderer, camera cam) override {
            if(!_is_alive)
                return;

            matrix temp = matrix::create_extra_row(_m);
            matrix result = temp*(cam.create_camera_matrix() * cam.create_projection_matrix());

            std::vector<point> points;

            for(int i = 0; i < result.get_columns(); i++){
                point p { result.get_value(0, i), result.get_value(1, i), result.get_value(2, i), result.get_value(3, i) };
                p = cam.correct_vector(p);
                points.push_back(p);
            }

            renderer.draw_line(points[0], points[1], 0, 255, 0);
            renderer.draw_line(points[0], points[3], 255, 255, 255);
            renderer.draw_line(points[0], points[4], 0, 255, 0);
            renderer.draw_line(points[1], points[2], 255, 255, 255);
            renderer.draw_line(points[1], points[5], 0, 255, 0);
            renderer.draw_line(points[2], points[3], 255, 0, 0);
            renderer.draw_line(points[2], points[6], 255, 0, 0);
            renderer.draw_line(points[3], points[7], 255, 0, 0);
            renderer.draw_line(points[4], points[5], 0, 255, 0);
            renderer.draw_line(points[4], points[7], 0, 255, 255);
            renderer.draw_line(points[5], points[6], 0, 255, 255);
            renderer.draw_line(points[6], points[7], 255, 0, 0);

            if(_draw_help_line){
                point vector = points[9] - points[8];
                vector = vector * 20;
                point _help_line = vector + points[8];
                //yellow aim line
                renderer.draw_line(points[8], _help_line, 255,255,0);
                //axis lines
                renderer.draw_line(points[8], points[9], 255,255,255);
                renderer.draw_line(points[8], points[10], 0, 255, 0);
                renderer.draw_line(points[8], points[11], 255, 0, 0);
            }
        };

        void handle_events(SDL_Event &event) override{
            bool button_pressed = event.key.type == SDL_KEYDOWN;

            switch (event.key.keysym.scancode){
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
                        _draw_help_line = !_draw_help_line;
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
