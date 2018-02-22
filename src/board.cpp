#include "board.h"
#include "point.h"
#include "board_piece.h"
#include <SDL2/SDL.h>

namespace linalg {
    board::board() : _window { "LINALG", 720, 720 },
                     _renderer { _window },
                     _square2d{{300.0, 300.0}, 100.0},
                     _cube{{ 0.0, 0.0, 50.0}, 10.0}{}


    void board::play() {
        bool playing = true;
        while(playing) {
            _renderer.clear();
            for(const auto a : _board_pieces) {
                a->draw(_renderer, _camera);
                a->update(0);
            }
            //_square2d.move_x_y(0.1, 0.10);
//            _square2d.rotate(0.01);
//
//            _square2d.update(0);
//            _square2d.draw(_renderer, _camera);
//            _cube.move_x_y_z(0.005,0,0);
//            _cube.move_x_y_z(0,-0.005,0);
//            _cube.move_x_y_z(0,0,-0.005);

            _cube.update(0);
            _cube.draw(_renderer, _camera);

            _renderer.render();
            
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                playing = (e.type != SDL_QUIT);
                _cube.handle_events(e);
            }
        }
    }
};
