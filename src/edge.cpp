#include "edge.h"
#include "node.h"
#include "point.h"

namespace linalg {
    float edge::distance() const {
        return linalg::distance(from().location(), to().location())*weight();
    }
}
