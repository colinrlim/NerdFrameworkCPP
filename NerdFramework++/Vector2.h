#pragma once

#include "Vector3.h"
struct Vector3;

struct Vector2
{
    double x;
    double y;

    Vector2(double x = 0.0, double y = 0.0);
    Vector2(double s);
    Vector2(const Vector2& a, const Vector2& b);
    Vector2(const Vector3& threedim);
    Vector2(uint16_t integer);

    static const Vector2 zero;
    static const Vector2 one;

    double magnitude() const;
    Vector2 normalized() const;
    uint16_t toInteger() const;
    void toInteger(uint16_t& integer) const;
    static Vector2 lerp(const Vector2& a, const Vector2& b, double alpha);
    static Vector2 fromParameterization3(double t, double s, const Vector2& a, const Vector2& b, const Vector2& c);

    Vector2& operator+=(const Vector2& rhs);
    Vector2& operator+=(double rhs);
    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator+(double rhs) const;
    Vector2& operator-=(const Vector2& rhs);
    Vector2& operator-=(double rhs);
    Vector2 operator-(const Vector2& rhs) const;
    Vector2 operator-(double rhs) const;
    Vector2 operator-() const;
    Vector2& operator*=(const Vector2& rhs);
    Vector2& operator*=(double rhs);
    Vector2 operator*(const Vector2& rhs) const;
    Vector2 operator*(double rhs) const;
    Vector2& operator/=(const Vector2& rhs);
    Vector2& operator/=(double rhs);
    Vector2 operator/(const Vector2& rhs) const;
    Vector2 operator/(double rhs) const;

    bool operator==(const Vector2& rhs) const;
    bool operator!=(const Vector2& rhs) const;
};

std::ostream& operator<<(std::ostream& stream, const Vector2& rhs);

