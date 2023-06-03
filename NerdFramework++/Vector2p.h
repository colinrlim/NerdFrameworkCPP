#pragma once

#include "Vector3.h"
#include "Vector2i.h"
struct Vector3;
struct Vector2i;

struct Vector2p
{
    // Radius
    double r;
    // Angle
    double theta;

    Vector2p(double r = 0.0, double theta = 0.0);
    Vector2p(double s);
    Vector2p(const Vector2& rectangular);

    static const Vector2p zero;

    Vector2 asRectangular() const;
    double hashTheta() const;

    void rotate(double radians);
    Vector2p rotated(double radians) const;

    template <typename iter>
    static void rotate(iter begin, iter end, double radians);
    template <typename iter, typename d_iter>
    static void rotated(iter begin, iter end, d_iter dest, double radians);

    static Vector2p lerp(const Vector2p& a, const Vector2p& b, double alpha);
    static Vector2p fromRandom(const Vector2p& min, const Vector2p& max);

    bool operator==(const Vector2p& rhs) const;
    bool operator!=(const Vector2p& rhs) const;
};

std::ostream& operator<<(std::ostream& stream, const Vector2& rhs);

