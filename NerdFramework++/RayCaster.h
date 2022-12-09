#pragma once

#include "Triangle3.h"
#include "Vector3s.h"
#include "Vector3.h"
#include "Ray3.h"

class RayCaster {
protected:
    Vector3s _spherical;

    RayCaster(const CameraRay3& direction) : d(direction) {}
    RayCaster(const CameraRay3& direction, const Vector3& width, const Vector3& height) :
        d(direction),
        w(width),
        h(height)
    {}

    friend class RayRadial;
    friend class RayRectangular;
    friend class RaySpherical;
public:
    CameraRay3 d;

    Vector3 w;
    Vector3 h;

    virtual Ray3 rayAt(double wAlpha, double hAlpha) = 0;
    virtual Vector3 vectorAt(double wAlpha, double hAlpha) = 0;
    virtual Vector2 projection(const Vector3& point) = 0;
    virtual bool meets(const Vector3& point) = 0;
    virtual bool meets(const Triangle3& triangle) = 0;
    virtual double distance(const Vector3& point) = 0;

    virtual void rotateX(double radians);
    virtual void rotateY(double radians);
    virtual void rotateZ(double radians);
    virtual void rotate(double r1, double r2, double r3);
    virtual void rotateTo(const Vector3& vector);
    virtual void rotateAbout(const Vector3& rotand, double radians);

    virtual void rotateZenith(double radians) = 0;
    virtual void rotatePolar(double radians) = 0;
};

