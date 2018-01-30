#include "base_systems.h"
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>

namespace linalg {

base_systems::base_systems() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0) {
        throw base_systems_init_error( std::string { "Error while initializing SDL: " } + SDL_GetError());
    }
    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_Quit();
        throw base_systems_init_error { std::string { "Error while initializing SDL_image: " } + IMG_GetError() };
    }
}

base_systems::~base_systems() {
    IMG_Quit();
    SDL_Quit();
}

} // namespace linalg
