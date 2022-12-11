#pragma once

#include "CameraRay3.h"
#include "Vector3s.h"
#include "Vector3.h"
struct Vector3s;
struct Vector3;

struct Ray3
{
    Vector3 p;
    Vector3 v;

    Ray3(const Vector3& position, const Vector3& vector);
    Ray3(const Vector3& position, const Vector3s& vector);
    Ray3(const CameraRay3& rayObject);

    static Ray3 lerp(const Ray3& a, const Ray3& b, double alpha);

    void rotateX(double radians);
    void rotateY(double radians);
    void rotateZ(double radians);
    void rotate(double r1, double r2, double r3);
    void rotateAbout(const Vector3& rotand, double radians);

    Ray3 operator+(const Ray3& rhs) const;
    Ray3 operator-(const Ray3& rhs) const;
    Ray3 operator*(const Ray3& rhs) const;
    Ray3 operator*(double rhs) const;
    Ray3 operator/(const Ray3& rhs) const;
    Ray3 operator/(double rhs) const;

    bool operator==(const Ray3& rhs) const;
    bool operator!=(const Ray3& rhs) const;
};

std::ostream& operator<<(std::ostream& stream, const Ray3& rhs);

