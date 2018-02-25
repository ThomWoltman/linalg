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
    class board {
        window _window;
        renderer _renderer;
        std::vector<board_piece*> _board_pieces;
        square _square2d;
        std::vector<cube*> _cubes;
        camera _camera;
        spaceship* _spaceship;
    public:
        board();
        ~board();
        renderer& get_renderer() { return _renderer; }
        void play();
        void add_board_piece(board_piece& a) {
            _board_pieces.push_back(&a);
        }
        void add_cube(cube* cube);
        std::vector<cube*>* get_cubes();
    };
}
#endif
