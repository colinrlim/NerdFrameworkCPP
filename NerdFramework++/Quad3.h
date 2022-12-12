#pragma once

#include "Triangle3.h"
#include "Vector3.h"
struct Triangle3;
struct Vector3;

struct Quad3
{
    Vector3& a;
    Vector3& b;
    Vector3& c;
    Vector3& d;

    Quad3(Vector3* a, Vector3* b, Vector3* c, Vector3* d);

    Triangle3 triangle1() const;
    Triangle3 triangle2() const;
};

std::ostream& operator<<(std::ostream& stream, const Quad3& rhs);

