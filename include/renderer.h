#ifndef _KMINT_RENDERER_H
#define _KMINT_RENDERER_H

#include "point.h"
#include "color.h"
#include <unordered_map>
#include "internal/texture.h"
#include <string>

struct SDL_Renderer;
struct SDL_Texture;

namespace linalg {
    class window;
    class image;
    
    class renderer {
        SDL_Renderer *_ren;
        mutable std::unordered_map<std::string, internal::texture> _texture_cache;
    public:
        renderer(const window &w);
        ~renderer();
        renderer(const renderer &) = delete;
        renderer& operator=(const renderer &) = delete;
        renderer(renderer &&);
        renderer& operator=(renderer &&);

        void clear() const;
        void set_color(color c) const;
        void draw_line(point from, point to) const;
        void draw_line(point from, point to, int R, int G, int B) const;
        void draw_rect(point topLeft, point bottomRight) const;
        void draw_image(point center, const image& i) const;
        void draw_polygon() const;
        void render() const;
    };
}

#endif
