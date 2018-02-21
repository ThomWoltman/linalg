#include "board.h"
#include "point.h"
#include "board_piece.h"
#include <SDL2/SDL.h>

namespace linalg {
    board::board() : _window { "LINALG", 1280, 720 },
                     _renderer { _window },
                     _square2d{{300.0, 300.0}, 100.0, 100.0}{}

    void board::play() {
        bool playing = true;
        while(playing) {
            _renderer.clear();
            for(const auto a : _board_pieces) {
                a->draw(_renderer);
                a->update(0);
            }
            _square2d.move_x_y(0.1, 0.10);
            _square2d.rotate(0.01);

            _square2d.update(0);
            _square2d.draw(_renderer);

            _renderer.render();
            
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                playing = (e.type != SDL_QUIT);
            }
        }
    }
};
