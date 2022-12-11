#pragma once

#include "Vector3.h"
#include "Line3.h"
struct Vector3;
struct Line3;

struct Plane3
{
    const Vector3& p;
    const Vector3& n;

    Plane3(const Vector3& position, const Vector3& normal);
    Plane3(const Vector3& a, const Vector3& b, const Vector3& c);

    bool meets(const Vector3& point) const;
    bool meets(const Line3& line) const;
    bool meets(const Plane3& plane) const;

    Vector3 intersection(const Line3& line) const;
    Line3 intersection(const Plane3& plane) const;

    double min(const Vector3& point) const;
    double min(const Line3& line) const;
    double min(const Plane3& plane) const;
};

std::ostream& operator<<(std::ostream& stream, const Plane3& rhs);

