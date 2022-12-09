#pragma once

#include "RayCaster.h"

class RayRadial : public RayCaster
{
private:
    double _angle;
public:
    RayRadial(const CameraRay3& direction, double angle);

    Ray3 rayAt(double wAlpha, double hAlpha);
    Vector3 vectorAt(double wAlpha, double hAlpha);
    Vector2 projection(const Vector3& point);
    bool meets(const Vector3& point);
    bool meets(const Triangle3& triangle);
    double distance(const Vector3& point);

    void rotateZenith(double radians);
    void rotatePolar(double radians);
};

