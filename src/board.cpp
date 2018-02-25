#include "board.h"
#include "point.h"
#include "board_piece.h"
#include <SDL2/SDL.h>
#include "spaceship.h"
#include "cube.h"

namespace linalg {
    board::board() : _window { "LINALG", 720, 720 },
                     _renderer { _window },
                     _square2d{{300.0, 300.0}, 100.0}{
        _spaceship = new spaceship { {0, 0, 50}, 2, 10, this };
        _cubes.push_back(new cube{{ 20, 0.0, 50.0}, 10.0, this});
//        _cubes.push_back(new cube{{ 20.0, 0.0, 50.0}, 10.0, this});
//        _cubes.push_back(new cube{{ 0.0, 100.0, 0.0}, 10.0, this});
//        _cubes.push_back(new cube{{ 0.0, -100.0, -50.0}, 10.0, this});
//        _cubes.push_back(new cube{{ -200.0, 0.0, -100.0}, 10.0, this});
    }

    board::~board() {
        { delete _spaceship;
            for( auto cube : _cubes){
                delete cube;
            }
        }
    }

    void board::play() {
        bool playing = true;
        while(playing) {
            _renderer.clear();
            for(const auto a : _board_pieces) {
                a->draw(_renderer, _camera);
                a->update(0);
            }

            _spaceship->update(0);


            for(auto cube : _cubes){
                cube->pulsate();
                cube->update(0);
                cube->draw(_renderer, _camera);
            }

//            for(auto cube : _cubes){
//                cube->update_is_alive();
//            }

            _spaceship->draw(_renderer, _camera);
            _camera.update();

            _renderer.render();
            
            SDL_Event e;
            while (SDL_PollEvent(&e)) {
                playing = (e.type != SDL_QUIT);
                //_cube1.handle_events(e);
                _spaceship->handle_events(e);
                _camera.handle_event(e);
            }
        }
    }

    void board::add_cube(cube *cube) {
        _cubes.push_back(cube);
    }

    std::vector<cube*>* board::get_cubes() {
        return &_cubes;
    }
};
