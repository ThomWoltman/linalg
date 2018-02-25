#include <iostream>
#include <stdexcept>
#include "base_systems.h"
#include "board.h"
#include "background.h"
#include "image.h"
#include <fstream>
#include <Vect3D.h>
#include <square.h>
#include "spaceship.h"
#include "cube.h"

int main() {
    try {

        std::cout << atan2(0, 0) << std::endl;
        std::cout << atan2(-30, -30) << std::endl;

        linalg::base_systems base {};
        linalg::board s {};

        s.add_spaceship(new linalg::spaceship { linalg::point{0, 0, 50}, 2, 10, &s });
        s.add_cube(new linalg::cube{{ 20, 0.0, 50.0}, 10.0, &s});
        s.add_cube(new linalg::cube{{ 20.0, 0.0, 50.0}, 10.0, &s});
        s.add_cube(new linalg::cube{{ 0.0, 100.0, 0.0}, 10.0, &s});
        s.add_cube(new linalg::cube{{ 0.0, -100.0, -50.0}, 10.0, &s});
        s.add_cube(new linalg::cube{{ -200.0, 0.0, -100.0}, 10.0, &s});

        s.play();
    }
    catch(const std::runtime_error &e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
    }
    return 0;
}
