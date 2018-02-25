#include "shape.h"
#include "cube.h"
#include "board.h"

namespace linalg {
    void shape::update_is_alive() {
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

    bool shape::is_colliding(std::vector<point> points) {
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

    point shape::get_x_axis() {
        point origin { _m.get_value(0,9), _m.get_value(1,9), _m.get_value(2,9)};
        return origin;
    }

    point shape::get_y_axis() {
        point origin { _m.get_value(0,10), _m.get_value(1,10), _m.get_value(2,10)};
        return origin;
    }

    point shape::get_z_axis() {
        point origin { _m.get_value(0,11), _m.get_value(1,11), _m.get_value(2,11)};
        return origin;
    }

    point shape::get_origin() {
        point origin { _m.get_value(0,8), _m.get_value(1,8), _m.get_value(2,8)};
        return origin;
    }

    void shape::rotate_x(double degree) {
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

    void shape::rotate_y(double degree) {
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

    void shape::rotate_z(double degree) {
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

    void shape::move_x_y_z(double amount_x, double amount_y, double amount_z) {
        _mutation = _mutation*matrix::create_translate_matrix_3d(amount_x, amount_y, amount_z);
    }

    void shape::do_mutation() {
        matrix temp = matrix::create_extra_row(_m);
        temp = temp * _mutation;
        _m = matrix::remove_extra_row(temp);
    }

    void shape::update_mutation() {
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

    void shape::scale(double amount_x, double amount_y, double amount_z) {
        _mutation = _mutation*matrix::create_scale_matrix_3d(amount_x, amount_y, amount_z);
    }
}