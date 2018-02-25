#ifndef _KMINT_BOARD_H
#define _KMINT_BOARD_H

#include "window.h"
#include "renderer.h"
#include "image.h"
#include "square.h"
#include <vector>

namespace linalg {
    class cube;
    class spaceship;
    class board_piece;
    class shape;
    class board {
        window _window;
        renderer _renderer;
        std::vector<board_piece*> _board_pieces;
        square _square2d;
        std::vector<shape*> _cubes;
        camera _camera;
        shape* _spaceship;
        bool _playing;
        void update();
        void draw();
        void handle_events();
    public:
        board();
        ~board();
        renderer& get_renderer() { return _renderer; }
        void play();
        void add_board_piece(board_piece& a) {
            _board_pieces.push_back(&a);
        }
        void add_cube(shape* cube);
        void add_spaceship(spaceship* spaceship);
        std::vector<shape*>* get_cubes();
    };
}
#endif
