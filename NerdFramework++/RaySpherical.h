#pragma once

#include "RayCaster.h"

class RaySpherical : public RayCaster
{
private:
    double _FOV;
    double _vertFOV;

    Vector3s _cameraTopLeft;
    Vector3 _bounds1;
    Vector3 _bounds2;
    Vector3 _bounds3;
    Vector3 _bounds4;

    void setAxes();
public:
    RaySpherical(const CameraRay3& direction, double vertCoefficient, double FOVinRadians);

    Ray3 rayAt(double wAlpha, double hAlpha);
    Vector3 vectorAt(double wAlpha, double hAlpha);
    Vector2 projection(const Vector3& point);
    bool meets(const Vector3& point);
    bool meets(const Triangle3& triangle);
    double distance(const Vector3& point);

    void rotateX(double radians);
    void rotateY(double radians);
    void rotateZ(double radians);
    void rotate(double r1, double r2, double r3);
    void rotateTo(const Vector3& vector);
    void rotateAbout(const Vector3& rotand, double radians);

    void rotateZenith(double radians);
    void rotatePolar(double radians);
};

