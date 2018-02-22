#ifndef KMINTFRAMEWORK_VECT3D_H
#define KMINTFRAMEWORK_VECT3D_H

#include "point.h"
#include "board_piece.h"

namespace linalg{
    class Vect3D : public point, public board_piece{
    private:
        point _origin;
    public:
        explicit Vect3D(point vector, point origin = point{}) : _origin{origin}, point{vector} {}
        void draw(renderer& renderer, camera) override{
            renderer.draw_line(_origin, _origin + *this);
        }
        point location() override { return _origin; }
    };
}

#endif //KMINTFRAMEWORK_VECT3D_H
