#pragma once

#include "Vector3.h"
#include "Vector2i.h"
struct Vector3;
struct Vector2i;

struct Vector2
{
    double x;
    double y;

    Vector2(double x = 0.0, double y = 0.0);
    Vector2(double s);
    Vector2(const Vector2& a, const Vector2& b);
    Vector2(const Vector2i& ivec);
    Vector2(const Vector3& threedim);
    Vector2(uint16_t integer);

    static const Vector2 zero;
    static const Vector2 one;

    void rotate(double radians);
    Vector2 rotated(double radians) const;

    template <typename iter>
    static void rotate(iter begin, iter end, double radians);
    template <typename iter, typename d_iter>
    static void rotated(iter begin, iter end, d_iter dest, double radians);

    double magnitude() const;
    Vector2 normalized() const;
    uint16_t toInteger() const;
    void toInteger(uint16_t& integer) const;
    static double dot(const Vector2& a, const Vector2& b);
    static Vector2 lerp(const Vector2& a, const Vector2& b, double alpha);
    static Vector2 fromParameterization3(double t, double s, const Vector2& a, const Vector2& b, const Vector2& c);
    static Vector2 fromRandom(const Vector2& min, const Vector2& max);

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

