#pragma once

#include "Vector3.h"
#include "Ray3.h"
struct Vector3;
struct Ray3;

struct Triangle3
{
public:
    Vector3& a;
    Vector3& b;
    Vector3& c;

    Triangle3(Vector3* a, Vector3* b, Vector3* c);

    Vector3 normal() const;
    double area() const;

    void move(const Vector3& offset);
    void scale(const Vector3& scale, const Vector3& origin);

    virtual void rotateX(double radians, const Vector3& origin) const;
    virtual void rotateY(double radians, const Vector3& origin) const;
    virtual void rotateZ(double radians, const Vector3& origin) const;
    virtual void rotate(double r1, double r2, double r3, const Vector3& origin) const;

    static Vector2 parameterization(const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& point);
    Vector2 parameterization(const Vector3& point) const;

    bool meets(const Vector3& point) const;
    bool meets(const Ray3& ray) const;
    /*bool meets(Triangle3 triangle);*/

    Vector3* ifMeetsGetIntersection(const Ray3& ray) const;
    Vector3 intersection(const Ray3& ray) const;

    /*double min(Vector3 point);*/
    /*double min(Ray3 ray);*/
    /*double min(Triangle3 triangle);*/
};

std::ostream& operator<<(std::ostream& stream, const Triangle3& rhs);

