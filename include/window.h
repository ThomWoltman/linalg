#ifndef _KMINT_WINDOW_H
#define _KMINT_WINDOW_H

#include <string>

struct SDL_Window;

namespace linalg {
    class renderer;

    class window {
        SDL_Window *_win;
    public:
        window(const std::string &title, int width, int height);
        ~window();
        window(const window &) = delete;
        window& operator=(const window&) = delete;

        window(window &&);
        window &operator=(window&&);

        friend class renderer;
    };
}
#endif
