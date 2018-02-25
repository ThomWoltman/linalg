#ifndef _KMINT_POINT_H
#define _KMINT_POINT_H

#include <istream>
#include <cmath>

namespace linalg {
    class point {
    public:
        using coord = double;
        point() : _x{0}, _y{0}, _z{0}, _w{0} {}
        point(coord x, coord y, coord z = 0) : _x{x}, _y{y}, _z{z}, _w{0} {}
        point(coord x, coord y, coord z, coord w) : _x{x}, _y{y}, _z{z}, _w{w} {}

        coord x() const noexcept { return _x; }
        void x(coord newX) noexcept { _x = newX; }
        coord y() const noexcept { return _y; }
        void y(coord newY) noexcept { _y = newY; }
        coord z() const noexcept { return _z; }
        void z(coord newZ) noexcept { _z = newZ; }
        coord w() const noexcept { return _w; }
        void w(coord newW) noexcept { _w = newW; }
    private:
        coord _x;
        coord _y;
        coord _z;
        coord _w;
    };

    std::istream &operator>>(std::istream &is, point &p);

    inline point operator-(point a, point b) {
        return { a.x() - b.x(), a.y() - b.y(), a.z() - b.z(), a.w() - b.w() };
    }

    inline bool operator==(point a, point b) {
        return a.x() == b.x() && a.y() == b.y() && a.z() == b.z();
    }

    inline point operator+(point a, point b) {
        return { a.x() + b.x(), a.y() + b.y(), a.z() + b.z(), a.w() + b.w() };
    }

    inline point operator*(point a, double multiplier) {
        return { a.x()*multiplier, a.y()*multiplier, a.z()*multiplier, a.w()*multiplier };
    }

    inline auto dot(point a, point b) { //inproduct
        return a.x()*b.x() + a.y()*b.y() + a.z()*b.z();
    }

    inline point cross_product(point a, point b) { //uitproduct
        return { a.y()*b.z() - a.z()*b.y(), a.z()*b.x() - a.x()*b.z(), a.x()*b.y() - a.y()*b.x() };
    }

    inline auto norm(point p) {
        return std::sqrt(dot(p, p));
    }

    inline point normalize(point p) {
        auto ls = norm(p);
        return { p.x() / ls, p.y() / ls, p.z() / ls, p.w() / ls };
    }

    inline auto distance(point from, point to) {
        return norm(to - from);
    }
}

#endif
