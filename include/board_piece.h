#ifndef _KMINT_ACTOR_H
#define _KMINT_ACTOR_H

#include "point.h"
#include "renderer.h"

namespace linalg {
    class drawable;
    class board_piece {
    public:
        board_piece() {}
        virtual ~board_piece() {};

        // remove copy and move operators and constructors
        board_piece(const board_piece&) = delete;
        board_piece(board_piece&&) = delete;
        board_piece& operator=(const board_piece&) = delete;
        board_piece& operator=(board_piece&&) = delete;
        
        virtual void update(float dt) {}
        virtual void draw(renderer& renderer) const = 0;
        virtual point location() const = 0;
    };
}

#endif
