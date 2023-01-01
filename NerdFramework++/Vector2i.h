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
    Vector2i(uint16_t integer);

    static const Vector2i zero;
    static const Vector2i one;

    void rotate(double radians);
    Vector2i rotated(double radians) const;

    double magnitude() const;
    Vector2i normalized() const;
    uint16_t toInteger() const;
    void toInteger(uint16_t& integer) const;
    static Vector2i fromParameterization3(double t, double s, const Vector2i& a, const Vector2i& b, const Vector2i& c);
    static Vector2i fromRandom(const Vector2i & min, const Vector2i & max);

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

std::ostream& operator<<(std::ostream& stream, const Vector2i& rhs);

