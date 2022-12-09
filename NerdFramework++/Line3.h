#pragma once

#include "Vector3.h"
struct Vector3;

struct Line3
{
    const Vector3& p;
    const Vector3& v;

    Line3(const Vector3& position, const Vector3& vector);

    bool meets(const Vector3& point) const;
    bool meets(const Line3& line) const;

    Vector3 intersection(const Line3& line) const;

    double min(const Vector3& point) const;
    double min(const Line3& line) const;
};

