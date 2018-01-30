#include <iostream>
#include <stdexcept>
#include "base_systems.h"
#include "board.h"
#include "background.h"
#include "image.h"
#include <fstream>
#include <Vect3D.h>

int main() {
    try {
        linalg::base_systems base {};
        linalg::board s {};
        linalg::background b { linalg::image { "resources/1200px-Hyades.jpg" } };

        linalg::Vect3D sample_vect{{800.0, 800.0}, {100.0, 20.0}};
        linalg::Vect3D sample_vect1{{800.0, 0}, {100.0, 100.0}};
        linalg::Vect3D sample_vect2{{800.0, 0, 200.0}, {100.0, 300.0}};
        linalg::Vect3D sample_vect3{{0, 0, -200.0}, {900.0, 300.0, 200.0}};

        s.add_board_piece(b);
//        s.add_board_piece(sample_vect);
//        s.add_board_piece(sample_vect1);
        s.add_board_piece(sample_vect2);
        s.add_board_piece(sample_vect3);


        s.play();
    }
    catch(const std::runtime_error &e) {
        std::cerr << "Runtime error: " << e.what() << "\n";
    }
    return 0;
}
