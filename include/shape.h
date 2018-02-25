#ifndef KMINTFRAMEWORK_SHAPE_H
#define KMINTFRAMEWORK_SHAPE_H

#include "matrix.h"
#include "camera.h"
#include "renderer.h"

namespace linalg {
    class board;
    class shape {
    protected:
        matrix _m;
        matrix _mutation;
        point _move;
        double pulse_value;
        double rotate_x_value = 0;
        double rotate_y_value = 0;
        double rotate_z_value = 0;
        double _move_speed = 0.01;
        bool _is_alive = true;
        board *_board;
    private:
    public:
        virtual ~shape(){};
        virtual void draw(renderer &renderer, camera cam) = 0;
        virtual void update(double dt) = 0;
        virtual void handle_events(SDL_Event &e){};
        virtual void update_is_alive();
        virtual void do_mutation();
        virtual void update_mutation();
        virtual point get_origin();
        virtual point get_x_axis();
        virtual point get_y_axis();
        virtual point get_z_axis();
        void move_x_y_z(double amount_x, double amount_y, double amount_z);
        void scale(double amount_x, double amount_y, double amount_z);
        virtual void pulsate(){};
        void rotate_x(double degree);
        void rotate_y(double degree);
        void rotate_z(double degree);
        void die(){ _is_alive = false; }
        bool is_colliding(std::vector<point> points);
    };
}

#endif //KMINTFRAMEWORK_SHAPE_H
