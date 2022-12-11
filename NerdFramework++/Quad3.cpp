#include "Quad3.h"

Quad3::Quad3(Vector3* a, Vector3* b, Vector3* c, Vector3* d) :
    a(*a),
    b(*b),
    c(*c),
    d(*d)
{
    /* A ----- D
     * |       |
     * |       |
     * |       |
     * B ----- C
     *
     * Normal points out of the page
     */
}

inline Triangle3 Quad3::getTriangle1() {
    return Triangle3(&a, &b, &c);
}
inline Triangle3 Quad3::getTriangle2() {
    return Triangle3(&a, &c, &d);
}

std::ostream& operator<<(std::ostream& stream, const Quad3& rhs) {
    return stream << "{ a: " << rhs.a << ", b: " << rhs.b << ", c: " << rhs.c << ", d: " << rhs.d << " }";
}