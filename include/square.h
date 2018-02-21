#ifndef KMINTFRAMEWORK_SQUARE_H
#define KMINTFRAMEWORK_SQUARE_H

#include "board_piece.h"
#include "matrix.h"

namespace linalg {
    class square : public board_piece {
    private:
        matrix _m;
        matrix _mutation;
        float _width;
        float _height;

        void init_matrix(point origin){
            std::vector<point> points;
            points.emplace_back(point{origin.x()-_width/2, origin.y()-_height/2});
            points.emplace_back(point{origin.x()-_width/2, origin.y()+_height/2});
            points.emplace_back(point{origin.x()+_width/2, origin.y()+_height/2});
            points.emplace_back(point{origin.x()+_width/2, origin.y()-_height/2});
            points.push_back(origin);

            _m = matrix(2, 5, points);
        }
    public:
        explicit square(point origin, float width, float height) : _width{width}, _height{height} {
            init_matrix(origin);
            init_mutation_matrix();
        };

        void init_mutation_matrix(){
            _mutation = matrix::create_identity_matrix(3);
        }

        void draw(renderer &renderer) override {

            std::vector<point> points;

            for(int i = 0; i < _m.get_columns() - 1; i++){
                point p { _m.get_value(0, i), _m.get_value(1, i) };
                points.push_back(p);
            }

            for(auto it = points.begin(); it != points.end(); it++){
                auto next = it + 1;
                if(next == points.end()){
                    next = points.begin();
                }
                renderer.draw_line(*it, *next);
            }
        };

        void update(float dt) override {
            matrix result = matrix::create_extra_row(_m) * _mutation;
            _m = matrix::remove_extra_row(result);
            init_mutation_matrix();
        }

        void move_x_y(double amount_x, double amount_y){
            matrix translate = matrix::create_translate_matrix(amount_x, amount_y);
            _mutation = _mutation * translate;
        }

        point get_origin(){
            point origin { _m.get_value(0,4), _m.get_value(1,4)};
            return origin;
        }

        void rotate(double degree){
            point origin = get_origin();

            move_x_y(-origin.x(), -origin.y());

            matrix rotate = matrix::create_rotate_matrix(degree);
            _mutation = _mutation * rotate;

            move_x_y(origin.x(), origin.y());
        }

        point location() override { return get_origin(); };
    };
}

#endif //KMINTFRAMEWORK_SQUARE_H
