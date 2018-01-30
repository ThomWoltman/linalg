#include "window.h"
#include "require.h"
#include <SDL2/SDL.h>
#include <stdexcept>

namespace linalg {
    window::window(const std::string &title, int width, int height) :
        _win { SDL_CreateWindow(title.c_str(),
                                SDL_WINDOWPOS_UNDEFINED,
                                SDL_WINDOWPOS_UNDEFINED,
                                width,
                                height,
                                SDL_WINDOW_OPENGL) } {
        require_sdl(_win);
    }

    window::~window() {
        if (_win) SDL_DestroyWindow(_win);
    }
    window::window(window &&other) : _win{other._win} {
        other._win = nullptr;
    }

    window &window::operator=(window&& other) {
        if (_win) {
            SDL_DestroyWindow(_win);
        }
        _win = other._win;
        other._win = nullptr;
        return *this;
    }
}
