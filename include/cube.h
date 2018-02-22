#include "board_piece.h"
#include "matrix.h"

#ifndef KMINTFRAMEWORK_CUBE_H
#define KMINTFRAMEWORK_CUBE_H

namespace linalg {

    class cube : public board_piece {
    private:
        matrix _m;
        matrix _mutation;
        double _width;
        point _move;

        void init_matrix(point origin) {
            std::vector<point> points;
            points.emplace_back(point{origin.x()-_width/2, origin.y()-_width/2, origin.z() - _width/2});
            points.emplace_back(point{origin.x()-_width/2, origin.y()+_width/2, origin.z() - _width/2});
            points.emplace_back(point{origin.x()+_width/2, origin.y()+_width/2, origin.z() - _width/2});
            points.emplace_back(point{origin.x()+_width/2, origin.y()-_width/2, origin.z() - _width/2});
            points.emplace_back(point{origin.x()-_width/2, origin.y()-_width/2, origin.z() + _width/2});
            points.emplace_back(point{origin.x()-_width/2, origin.y()+_width/2, origin.z() + _width/2});
            points.emplace_back(point{origin.x()+_width/2, origin.y()+_width/2, origin.z() + _width/2});
            points.emplace_back(point{origin.x()+_width/2, origin.y()-_width/2, origin.z() + _width/2});
            points.push_back(origin);

            _m = matrix(3, 9, points);
        }

        void init_mutation_matrix(){
            _mutation = matrix::create_identity_matrix(4);
        }
    public:
        cube(point origin, double width) : _width{width} {
            init_matrix(origin);
            init_mutation_matrix();
        };

        void draw(renderer &renderer, camera cam) override {

            matrix temp = matrix::create_extra_row(_m);
            matrix result = temp*(cam.create_camera_matrix() * cam.create_projection_matrix());

            std::vector<point> points;

            for(int i = 0; i < result.get_columns() - 1; i++){
                point p { result.get_value(0, i), result.get_value(1, i), result.get_value(2, i), result.get_value(3, i) };
                p = cam.correct_vector(p);
                points.push_back(p);
            }


            renderer.draw_line(points[0], points[1], 255, 0, 0);
            renderer.draw_line(points[0], points[3], 255, 0, 0);
            renderer.draw_line(points[0], points[4]);
            renderer.draw_line(points[1], points[2], 255, 0, 0);
            renderer.draw_line(points[1], points[5]);
            renderer.draw_line(points[2], points[3], 255, 0, 0);
            renderer.draw_line(points[2], points[6]);
            renderer.draw_line(points[3], points[7]);
            renderer.draw_line(points[4], points[5], 255, 230, 0);
            renderer.draw_line(points[4], points[7], 255, 230, 0);
            renderer.draw_line(points[5], points[6], 255, 230, 0);
            renderer.draw_line(points[6], points[7], 255, 230, 0);
        };

        void update(double dt) override {
            init_mutation_matrix();
            update_mutation();
            do_mutation();
        }

        void do_mutation(){
            matrix temp = matrix::create_extra_row(_m);
            temp = temp * _mutation;
            _m = matrix::remove_extra_row(temp);
        }

        void update_mutation(){
            if(_move.x() != 0 || _move.y() != 0 || _move.z() != 0)
                move_x_y_z(_move.x(), _move.y(), _move.z());
        }

        void move_x_y_z(double amount_x, double amount_y, double amount_z){
            _mutation = _mutation*matrix::create_translate_matrix_3d(amount_x, amount_y, amount_z);
        }

        point get_origin(){
            point origin { _m.get_value(0,8), _m.get_value(1,8)};
            return origin;
        }

        void rotate(double degree){

        }

        point location() override { return get_origin(); };

        void handle_events(SDL_Event &event){
            bool button_pressed = event.key.type == SDL_KEYDOWN;

            switch (event.key.keysym.scancode){
                case SDL_SCANCODE_W :
                    if(button_pressed){
                        _move.y(0.01);
                    }
                    else{
                        _move.y(0);
                    }
                    break;
                case SDL_SCANCODE_S :
                    if(button_pressed){
                        _move.y(-0.01);
                    }
                    else{
                        _move.y(0);
                    }
                    break;
                case SDL_SCANCODE_D :
                    if(button_pressed){
                        _move.x(0.01);
                    }
                    else{
                        _move.x(0);
                    }
                    break;
                case SDL_SCANCODE_A :
                    if(button_pressed){
                        _move.x(-0.01);
                    }
                    else{
                        _move.x(0);
                    }
                    break;
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
                default:
                    break;
            }
        }
    };
}

#endif //KMINTFRAMEWORK_CUBE_H

