#ifndef _KMINT_BACKGROUND_H
#define _KMINT_BACKGROUND_H

#include "point.h"
#include "free_roaming_board_piece.h"
#include "image.h"

namespace linalg {
    class background : public free_roaming_board_piece {
    private:
        image _i;
    public:
        explicit background(const image &i) : free_roaming_board_piece { {640.0, 360.0} }, _i{i} {}
        void draw(renderer& renderer) override;
    };
}

#endif
