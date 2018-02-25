#include "board_piece.h"
#include "matrix.h"
#include "board.h"
#include "shape.h"

#ifndef KMINTFRAMEWORK_CUBE_H
#define KMINTFRAMEWORK_CUBE_H

namespace linalg {

    class cube : public shape {
    protected:
        double _width;
    private:

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

            points.emplace_back(point { origin.x() + _width/2, origin.y(), origin.z()}); //local x-axis
            points.emplace_back(point { origin.x(), origin.y() + _width/2, origin.z()}); //local y-axis
            points.emplace_back(point { origin.x(), origin.y(), origin.z() + -_width/2}); //local z-axis

            _m = matrix(3, 12, points);
        }
    public:
        void init_mutation_matrix(){
            _mutation = matrix::create_identity_matrix(4);
        }

        cube(point origin, double width, board* board) : _width{width} {
            _board = board;
            init_matrix(origin);
            init_mutation_matrix();
        };

        cube(point origin, double width, double speed_x, double speed_y, double speed_z, board* board) : _width{width} {
            _board = board;
            init_matrix(origin);
            init_mutation_matrix();

            _move = {speed_x, speed_y, speed_z};
        };

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
            renderer.draw_line(points[8], points[9], 255,255,255);
            renderer.draw_line(points[8], points[10], 0, 255, 0);
            renderer.draw_line(points[8], points[11], 255, 0, 0);
        };

        void update(double dt) override {
            if(!_is_alive)
                return;
            update_mutation();
            do_mutation();
            init_mutation_matrix();
        }

        void pulsate() override{
            point a { _m.get_value(0,0), _m.get_value(1,0), _m.get_value(2,0) };
            point b { _m.get_value(0,1), _m.get_value(1,1), _m.get_value(2,1) };

            double dist = distance(a, b);

            if(dist > _width + 2) {
                pulse_value = 0.9995;
            }
            else if(dist <= _width){
                pulse_value = 1.0005;
            }

            //pulse_value = 1.000001;
            point origin = get_origin();
            move_x_y_z(-origin.x(), -origin.y(), -origin.z());
            scale(pulse_value, pulse_value, pulse_value);
            move_x_y_z(origin.x(), origin.y(), origin.z());
        }
    };
}

#endif //KMINTFRAMEWORK_CUBE_H

