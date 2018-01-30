#ifndef _KMINT_EDGE_H
#define _KMINT_EDGE_H

namespace linalg {
    class node;
    class edge {
        const node* _from;
        const node* _to;
        float _weight;
    public:
        edge(const node& from, const node &to, float weight = 1.0f) : _from {&from}, _to {&to}, _weight { weight } {}
        const node& to() const noexcept { return *_to; }
        const node& from() const noexcept { return *_from; }
        float distance() const;
        float weight() const noexcept { return _weight; }
    };
}

#endif
