#include "renderer.h"
#include "window.h"
#include "require.h"
#include "image.h"
#include <iostream>
#include <SDL2/SDL.h>

namespace linalg {

    renderer::renderer(const window &w)
        : _ren { SDL_CreateRenderer(w._win, -1, SDL_RENDERER_ACCELERATED) },
          _texture_cache {}
    {
        require_sdl(_ren);
    }

    renderer::~renderer() {
        _texture_cache.clear();
        if (_ren) SDL_DestroyRenderer(_ren);
    }

    renderer::renderer(renderer &&other) : _ren {other._ren} {
        other._ren = nullptr;
    }

    renderer& renderer::operator=(renderer &&other) {
        if (_ren) SDL_DestroyRenderer(_ren);
        _ren = other._ren;
        other._ren = nullptr;
        return *this;
    }

    void renderer::clear() const {
        SDL_SetRenderDrawColor(_ren, 0, 0, 0, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(_ren);
    }

    void renderer::set_color(color c) const {
        SDL_SetRenderDrawColor(_ren, c.r(), c.g(), c.b(), c.a());
    }

    void renderer::draw_line(point from, point to) const {
        set_color(color{100,100,255});
        SDL_RenderDrawLine(_ren, from.x(), 720 - (from.y()+from.z()), to.x(), 720 - (to.y() + to.z()));
    }

    void renderer::draw_rect(point topLeft, point bottomRight) const {
        SDL_Rect r;
        r.x = topLeft.x();
        r.y = topLeft.y();
        r.w = bottomRight.x() - topLeft.x();
        r.h = bottomRight.y() - topLeft.y();
        SDL_RenderFillRect(_ren, &r);
    }

    void renderer::draw_image(point center, const image &i) const {
        auto texture_it = _texture_cache.find(i.filename());
        if (texture_it == _texture_cache.end())
            texture_it = _texture_cache.emplace(i.filename(), internal::texture { i.filename() , _ren}).first;
        const auto &texture = texture_it->second;
        auto w = texture.width() * i.scale();
        auto h = texture.height() * i.scale();
        auto x = center.x() - w/2.0;
        auto y = center.y() - h/2.0;

        SDL_Rect r;
        r.x = x;
        r.y = y;
        r.w = w;
        r.h = h;
        SDL_RenderCopy(_ren, texture.unwrap(), nullptr, &r);
    }

    void renderer::render() const {
        SDL_RenderPresent(_ren);
    }
}
