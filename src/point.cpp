#include "point.h"

namespace linalg {
    std::istream &operator>>(std::istream &is, point &p) {
        point::coord x, y;
        if (is >> x && is >> y) {
            p.x(x);
            p.y(y);
        }
        return is;
    }
}
