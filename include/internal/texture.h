#ifndef _KMINT_INTERNAL_TEXTURE_H
#define _KMINT_INTERNAL_TEXTURE_H

#include <string>
#include <iostream>
#include <SDL2/SDL.h>

namespace linalg {
    namespace internal {
        class texture {
            SDL_Texture *_texture;
            float _width;
            float _height;
        public:
            texture(const std::string &filename, SDL_Renderer *ren);
            texture(texture&&);
            texture& operator=(texture&&);
            texture(const texture&) = delete;
            texture& operator=(const texture&) = delete;
            ~texture();
            SDL_Texture *unwrap() const { return _texture; }
            float width() const { return _width; }
            float height() const { return _height; }
        };
    }
}
#endif
