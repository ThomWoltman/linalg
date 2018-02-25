#include "board_piece.h"
#include "matrix.h"
#include "board.h"

#ifndef KMINTFRAMEWORK_CUBE_H
#define KMINTFRAMEWORK_CUBE_H

namespace linalg {

    class cube : public board_piece {
    protected:
        matrix _m;
        matrix _mutation;
        double _width;
        point _move;
        double pulse_value;
        double rotate_x_value = 0;
        double rotate_y_value = 0;
        double rotate_z_value = 0;
        double _move_speed = 0.01;
        bool _draw_help_line = false;
        point _help_line;
        bool _is_alive = true;
        board *_board;
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

        cube(point origin, double width, board* board) : _width{width}, _board{board} {
            init_matrix(origin);
            init_mutation_matrix();
        };

        cube(point origin, double width, double speed_x, double speed_y, double speed_z, board* board) : _width{width}, _board{board} {
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

            if(_draw_help_line){
                point vector = points[9] - points[8];
                vector = vector * 20;
                _help_line = vector + points[8];
                renderer.draw_line(points[8], _help_line, 255,255,0);
            }
        };

        virtual void update(double dt) override {
            if(!_is_alive)
                return;
            update_mutation();
            do_mutation();
            init_mutation_matrix();
        }

        void update_is_alive(){
            auto cubes = _board->get_cubes();

            std::vector<point> points;

            for(int i = 0; i < _m.get_columns(); i++){
                point p { _m.get_value(0, i), _m.get_value(1, i), _m.get_value(2, i) };
                points.push_back(p);
            }

            for(auto c : *cubes){
                if(!(c->get_origin() == points[8])) {
                    if (c->is_colliding(points)) {
                        die();
                        c->die();
                    }
                }
            }
        }

        void do_mutation(){
            matrix temp = matrix::create_extra_row(_m);
            temp = temp * _mutation;
            _m = matrix::remove_extra_row(temp);
        }

        virtual void update_mutation(){
            if(_move.x() != 0 || _move.y() != 0 || _move.z() != 0){
                move_x_y_z(_move.x(), _move.y(), _move.z());
            }
            if(rotate_x_value != 0)
                rotate_x(rotate_x_value);
            if(rotate_y_value != 0)
                rotate_y(rotate_y_value);
            if(rotate_z_value != 0)
                rotate_z(rotate_z_value);
        }

        void move_x_y_z(double amount_x, double amount_y, double amount_z){
            _mutation = _mutation*matrix::create_translate_matrix_3d(amount_x, amount_y, amount_z);
        }

        void scale(double amount_x, double amount_y, double amount_z){
            _mutation = _mutation*matrix::create_scale_matrix_3d(amount_x, amount_y, amount_z);
        }

        void pulsate(){
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

        point get_origin(){
            point origin { _m.get_value(0,8), _m.get_value(1,8), _m.get_value(2,8)};
            return origin;
        }

        point get_x_axis(){
            point origin { _m.get_value(0,9), _m.get_value(1,9), _m.get_value(2,9)};
            return origin;
        }

        point get_y_axis(){
            point origin { _m.get_value(0,10), _m.get_value(1,10), _m.get_value(2,10)};
            return origin;
        }

        point get_z_axis(){
            point origin { _m.get_value(0,11), _m.get_value(1,11), _m.get_value(2,11)};
            return origin;
        }

        void rotate_x(double degree){
            point origin = get_origin();
            point x_axis = get_x_axis();

            point new_x_axis = x_axis - origin;

            double t1 = atan2(new_x_axis.z(), new_x_axis.x());
            double t2 = atan2(new_x_axis.y(), sqrt(new_x_axis.x()*new_x_axis.x() + new_x_axis.z()*new_x_axis.z()));

            move_x_y_z(-origin.x(), -origin.y(), -origin.z());

            matrix rotate_y_inverse = matrix::create_rotate_y_matrix_3d(-t1);
            matrix rotate_z_inverse = matrix::create_rotate_z_matrix_3d(-t2);

            matrix rotate_x = matrix::create_rotate_x_matrix_3d(degree);

            matrix rotate_z = matrix::create_rotate_z_matrix_3d(t2);
            matrix rotate_y = matrix::create_rotate_y_matrix_3d(t1);

            _mutation = _mutation*(rotate_y_inverse*rotate_z_inverse*rotate_x*rotate_z*rotate_y);

            move_x_y_z(origin.x(), origin.y(), origin.z());
        }

        void rotate_y(double degree){
            point origin = get_origin();
            point y_axis = get_y_axis();

            point new_y_axis = y_axis - origin;

            double t1 = atan2(new_y_axis.z(), new_y_axis.y());
            double t2 = atan2(new_y_axis.x(), sqrt(new_y_axis.z()*new_y_axis.z() + new_y_axis.y()*new_y_axis.y()));

            move_x_y_z(-origin.x(), -origin.y(), -origin.z());

            matrix rotate_x_inverse = matrix::create_rotate_x_matrix_3d(-t1);
            matrix rotate_z_inverse = matrix::create_rotate_z_matrix_3d(t2);

            matrix rotate_y = matrix::create_rotate_y_matrix_3d(degree);

            matrix rotate_z = matrix::create_rotate_z_matrix_3d(-t2);
            matrix rotate_x = matrix::create_rotate_x_matrix_3d(t1);

            _mutation = _mutation*(rotate_x_inverse*rotate_z_inverse*rotate_y*rotate_z*rotate_x);

            move_x_y_z(origin.x(), origin.y(), origin.z());
        }

        void rotate_z(double degree){
            point origin = get_origin();
            point z_axis = get_z_axis();

            point new_z_axis = z_axis - origin;

            double t1 = atan2(new_z_axis.y(), new_z_axis.z());
            double t2 = atan2(new_z_axis.x(), sqrt(new_z_axis.z()*new_z_axis.z() + new_z_axis.y()*new_z_axis.y()));

            move_x_y_z(-origin.x(), -origin.y(), -origin.z());

            matrix rotate_x_inverse = matrix::create_rotate_x_matrix_3d(t1);
            matrix rotate_y_inverse = matrix::create_rotate_y_matrix_3d(t2);

            matrix rotate_z = matrix::create_rotate_z_matrix_3d(degree);

            matrix rotate_y = matrix::create_rotate_y_matrix_3d(-t2);
            matrix rotate_x = matrix::create_rotate_x_matrix_3d(-t1);

            _mutation = _mutation*(rotate_x_inverse*rotate_y_inverse*rotate_z*rotate_y*rotate_x);

            move_x_y_z(origin.x(), origin.y(), origin.z());
        }

        point location() override { return get_origin(); };

        void die(){
            _is_alive = false;
        }

        bool is_colliding(std::vector<point> points){
            if(points[8] == get_origin())
                return false;
            point p { round(_m.get_value(0, 2)*1000), round(_m.get_value(1, 2)*1000), round(_m.get_value(2, 2)*1000) };
            point q { round(_m.get_value(0, 3)*1000), round(_m.get_value(1, 3)*1000), round(_m.get_value(2, 3)*1000) };
            point s { round(_m.get_value(0, 6)*1000), round(_m.get_value(1, 6)*1000), round(_m.get_value(2, 6)*1000) };
            point t { round(_m.get_value(0, 7)*1000), round(_m.get_value(1, 7)*1000), round(_m.get_value(2, 7)*1000) };

            point pq = q - p;
            point ps = s - p;

            point tq = q- t;
            point ts = s- t;

            point normalize_n1 = cross_product(pq, ps);
            point normalize_n2 = cross_product(tq, ts);

            double result1 = dot(normalize_n1, p);
            double result2 = dot(normalize_n2, t);

            double example = dot(q, normalize_n1);

            for(auto p1 : points){
                point rounded_point = { round(p1.x()*1000), round(p1.y()*1000), round(p1.z()*1000)};
                double value1 = dot(rounded_point, normalize_n1);
                double value2 = dot(rounded_point, normalize_n2);
                if(value1 == result1 || value2 == result2){
                    return true;
                }
            }

            return false;
        }
    };
}

#endif //KMINTFRAMEWORK_CUBE_H

