#pragma once

#include "Vector3s.h"
#include "Vector3.h"
struct Vector3s;
struct Vector3;

class CameraRay3
{
public:
    Vector3& p;
    Vector3 v;

    CameraRay3(Vector3* position, const Vector3& vector);
    CameraRay3(Vector3* position, const Vector3s& vector);

    void rotateX(double radians);
    void rotateY(double radians);
    void rotateZ(double radians);
    void rotate(double r1, double r2, double r3);
    void rotateAbout(const Vector3& rotand, double radians);
};

