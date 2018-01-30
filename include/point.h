#ifndef _KMINT_POINT_H
#define _KMINT_POINT_H

#include <istream>
#include <cmath>

namespace linalg {
    class point {
    public:
        using coord = float;
        point() : _x{0}, _y{0}, _z{0} {}
        point(coord x, coord y, coord z = 0) : _x{x}, _y{y}, _z{z} {}
        coord x() const noexcept { return _x; }
        void x(coord newX) noexcept { _x = newX; }
        coord y() const noexcept { return _y; }
        void y(coord newY) noexcept { _y = newY; }
        coord z() const noexcept { return _z; }
        void z(coord newZ) noexcept { _z = newZ; }
    private:
        coord _x;
        coord _y;
        coord _z;
    };

    std::istream &operator>>(std::istream &is, point &p);

    inline point operator-(point a, point b) {
        return { a.x() - b.x(), a.y() - b.y(), a.z() - b.z() };
    }

    inline point operator+(point a, point b) {
        return { a.x() + b.x(), a.y() + b.y(), a.z() + b.z() };
    }

    inline auto dot(point a, point b) {
        return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
    }

    inline point normalize(point p) {
        auto ls = dot(p, p);
        return { p.x() / ls, p.y() / ls, p.z() / ls };
    }

    inline auto norm(point p) {
        return std::sqrt(dot(p, p));
    }

    inline auto distance(point from, point to) {
        return norm(to - from);
    }
}

#endif
