#ifndef _KMINT_INTERNAL_SURFACE_H
#define _KMINT_INTERNAL_SURFACE_H

#include <string>

struct SDL_Surface;

namespace linalg {
    namespace internal {
        class surface {
            SDL_Surface *_surface;
        public:
            surface(const std::string &filename);
            ~surface();

            surface(const surface&) = delete;;
            surface& operator=(const surface&) = delete;
            surface(surface&&);
            surface& operator=(surface&&);

            SDL_Surface *unwrap() const { return _surface; }
        };
    }
}
#endif
