#pragma once

#include "Vector3.h"
struct Vector3;

struct Vector2i
{
    int x;
    int y;

    Vector2i(int x = 0, int y = 0);
    Vector2i(int s);
    Vector2i(const Vector2i& a, const Vector2i& b);
    Vector2i(const Vector3& threedim);

    static const Vector2i zero;
    static const Vector2i one;

    double magnitude();
    Vector2i normalized();
    static Vector2i fromParameterization3(double t, double s, const Vector2i& a, const Vector2i& b, const Vector2i& c);

    Vector2i& operator+=(const Vector2i& rhs);
    Vector2i& operator+=(int rhs);
    Vector2i operator+(const Vector2i& rhs) const;
    Vector2i operator+(int rhs) const;
    Vector2i& operator-=(const Vector2i& rhs);
    Vector2i& operator-=(int rhs);
    Vector2i operator-(const Vector2i& rhs) const;
    Vector2i operator-(int rhs) const;
    Vector2i operator-() const;
    Vector2i& operator*=(const Vector2i& rhs);
    Vector2i& operator*=(int rhs);
    Vector2i operator*(const Vector2i& rhs) const;
    Vector2i operator*(int rhs) const;
    Vector2i& operator/=(const Vector2i& rhs);
    Vector2i& operator/=(int rhs);
    Vector2i operator/(const Vector2i& rhs) const;
    Vector2i operator/(int rhs) const;

    bool operator==(const Vector2i& rhs) const;
    bool operator!=(const Vector2i& rhs) const;
};

