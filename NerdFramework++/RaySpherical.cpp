#include "RaySpherical.h"
#include "Plane3.h"
#include "Math.h"

void RaySpherical::setAxes() {
    this->w = Vector3(_spherical.rotatedPolar(-HALF_PI));
    this->h = Vector3(_spherical.rotatedZenith(-HALF_PI));

    this->_bounds1 = Vector3(_spherical.rotatedPolar(this->_FOV / 2.0));
    this->_bounds2 = Vector3(_spherical.rotatedPolar(-this->_FOV / 2.0));
    this->_bounds3 = Vector3(_spherical.rotatedZenith(this->_vertFOV / 2.0));
    this->_bounds4 = Vector3(_spherical.rotatedZenith(-this->_vertFOV / 2.0));

    this->_cameraTopLeft = _spherical.rotatedPolar(-this->_FOV / 2.0).rotatedZenith(-this->_vertFOV / 2.0);
}

RaySpherical::RaySpherical(const CameraRay3& direction, double vertCoefficient, double FOVinRadians) : RayCaster(direction) {
    this->d.v = Vector3::zAxis;
    this->_FOV = FOVinRadians;
    this->_vertFOV = FOVinRadians * vertCoefficient;

    double c = Math::cos(this->_FOV);

    this->rotateTo(direction.v);
}

Ray3 RaySpherical::rayAt(double wAlpha, double hAlpha) {
    return Ray3(this->d.p, this->vectorAt(wAlpha, hAlpha));
}
Vector3 RaySpherical::vectorAt(double wAlpha, double hAlpha) {
    return Vector3(this->_spherical.rotatedPolar(-(wAlpha - 0.5) / this->_FOV).rotatedZenith(-(hAlpha - 0.5) / this->_vertFOV));
}
Vector2 RaySpherical::projection(const Vector3& point) {
    Vector3s pointSpherical = Vector3s(point - this->d.p);
    Vector2 diff = Vector2(pointSpherical.theta - this->_cameraTopLeft.theta, pointSpherical.phi - this->_cameraTopLeft.phi);

    return Vector2(
        1.0 - (diff.x >= 0.0 ? (diff.x < TWO_PI ? diff.x : diff.x - TWO_PI) : diff.x + TWO_PI) / this->_FOV,
        1.0 - (diff.y >= 0.0 ? (diff.y < PI ? diff.y : diff.y - PI) : diff.y + PI) / this->_vertFOV);
}
bool RaySpherical::meets(const Vector3& point) {
    Vector3s pointSpherical = Vector3s(point - this->d.p);
    Vector3s diff = Vector3s::min(pointSpherical, this->_spherical);
    return diff.theta <= this->_FOV / 2.0 && diff.phi <= this->_vertFOV / 2.0;
}
bool RaySpherical::meets(const Triangle3& triangle) {
    Vector3 normal = triangle.normal();
    return (
        Vector3::dot(this->_bounds1, normal) < 0.0 ||
        Vector3::dot(this->_bounds2, normal) < 0.0 ||
        Vector3::dot(this->_bounds3, normal) < 0.0 ||
        Vector3::dot(this->_bounds4, normal) < 0.0) &&
        (this->meets(triangle.a) || this->meets(triangle.b) || this->meets(triangle.c));
}
double RaySpherical::distance(const Vector3& point) {
    Plane3 plane = Plane3(this->d.p, this->d.v);
    return plane.min(point);
}

void RaySpherical::rotateX(double radians) {
    this->d.rotateX(radians);
    this->_spherical = Vector3s(this->d.v);
    this->setAxes();
}
void RaySpherical::rotateY(double radians) {
    this->d.rotateY(radians);
    this->_spherical = Vector3s(this->d.v);
    this->setAxes();
}
void RaySpherical::rotateZ(double radians) {
    this->d.rotateZ(radians);
    this->_spherical = Vector3s(this->d.v);
    this->setAxes();
}
void RaySpherical::rotate(double r1, double r2, double r3) {
    this->d.rotate(r1, r2, r3);
    this->_spherical = Vector3s(this->d.v);
    this->setAxes();
}
void RaySpherical::rotateTo(const Vector3& vector) {
    Vector3 rotation = Vector3::angle3(this->d.v, vector);
    this->rotate(rotation.x, rotation.y, rotation.z);
}
void RaySpherical::rotateAbout(const Vector3& rotand, double radians) {
    this->d.rotateAbout(rotand, radians);
    this->_spherical = Vector3s(d.v);
    this->setAxes();
}

void RaySpherical::rotateZenith(double radians) {
    this->_spherical = this->_spherical.rotatedZenith(radians);
    this->d.v =  Vector3(this->_spherical);
    this->setAxes();
}
void RaySpherical::rotatePolar(double radians) {
    this->_spherical = this->_spherical.rotatedPolar(radians);
    this->d.v = Vector3(this->_spherical);
    this->setAxes();
}