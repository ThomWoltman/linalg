#include "board.h"
#include "point.h"
#include "board_piece.h"
#include <SDL2/SDL.h>
#include "spaceship.h"
#include "cube.h"

namespace linalg {
    board::board() : _window { "LINALG", 720, 720 },
                     _renderer { _window },
                     _square2d{{300.0, 300.0}, 100.0}{}

    board::~board() {
        { delete _spaceship;
            for( auto cube : _cubes){
                delete cube;
            }
        }
    }

    void board::play() {
        _playing = true;
        while(_playing) {
            _renderer.clear();

            handle_events();
            update();
            draw();

            _renderer.render();
        }
    }

    void board::update() {
        _spaceship->update(0);
        for(auto cube : _cubes){
            cube->pulsate();
            cube->update(0);
        }
    }

    void board::draw() {
        for(auto cube : _cubes){
            cube->draw(_renderer, _camera);
        }
        _spaceship->draw(_renderer, _camera);
        _camera.update();
    }

    void board::handle_events() {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            _playing = (e.type != SDL_QUIT);
            //_cube1.handle_events(e);
            _spaceship->handle_events(e);
            _camera.handle_event(e);
        }
    }

    void board::add_cube(cube *cube) {
        _cubes.push_back(cube);
    }

    void board::add_spaceship(spaceship *spaceship) {
        _spaceship = spaceship;
    }

    std::vector<cube*>* board::get_cubes() {
        return &_cubes;
    }
};
