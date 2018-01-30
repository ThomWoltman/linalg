#ifndef _KMINT_NODE_H
#define _KMINT_NODE_H

#include <vector>
#include "point.h"
#include "edge.h"

namespace linalg {
    class node {
        point _location;
        int _id;
        std::vector<edge> _edges;
    public:
        node(point location, int id) : _location {location}, _id {id}, _edges {} {}
        int id() const noexcept { return _id; }
        point location() const noexcept { return _location; }
        void add_edge(edge e) { _edges.push_back(e); }
        decltype(auto) begin() const noexcept { return _edges.begin(); }
        decltype(auto) end() const noexcept { return _edges.end(); }
    };
}

#endif
