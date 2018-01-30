#include "internal/surface.h"
#include <SDL_image.h>
#include <stdexcept>

namespace linalg {
    namespace internal {

        surface::surface(const std::string &filename) {
            _surface = IMG_Load(filename.c_str());
            if (!_surface) {
                throw std::runtime_error { "Error while loading \"" + filename + "\": " + IMG_GetError() };
            }
        }

        surface::surface(surface&& other) : _surface { other._surface } {
            other._surface = nullptr;
        }

        surface& surface::operator=(surface &&other) {
            if (_surface) SDL_FreeSurface(_surface);
            _surface = other._surface;
            other._surface = nullptr;
            return *this;
        }

        surface::~surface() {
            if (_surface) SDL_FreeSurface(_surface);
        }
    }
}
