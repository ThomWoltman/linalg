#include "board.h"
#include "point.h"
#include "board_piece.h"
#include <SDL2/SDL.h>

namespace linalg {
    board::board() : _window { "LINALG", 1280, 720 },
                     _renderer { _window } {}

    void board::play() {
        bool playing = true;
        while(playing) {
            _renderer.clear();
            for(const auto a : _board_pieces) {
                a->draw(_renderer);
            }
            _renderer.render();
            
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                playing = (e.type != SDL_QUIT);
            }
        }
    }
};
