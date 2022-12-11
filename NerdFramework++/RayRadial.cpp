#include "RayRadial.h"

RayRadial::RayRadial(const CameraRay3& direction, double angle) :
    RayCaster(direction, Vector3::xAxis, Vector3::yAxis)
{
    this->d.v = Vector3::zAxis;
    this->_angle = angle;

    this->rotateTo(direction.v);
}

inline Ray3 RayRadial::rayAt(double wAlpha, double hAlpha) {
    throw "myFunction is not implemented yet.";
}
inline Vector3 RayRadial::vectorAt(double wAlpha, double hAlpha) {
    throw "myFunction is not implemented yet.";
}
inline Vector2 RayRadial::projection(const Vector3& point) {
    throw "myFunction is not implemented yet.";
}
inline bool RayRadial::meets(const Vector3& point) {
    return Vector3::angle(d.v, point - d.p) <= _angle / 2.0;
}
inline bool RayRadial::meets(const Triangle3& triangle) {
    throw "myFunction is not implemented yet.";
}
inline double RayRadial::distance(const Vector3& point) {
    return (point - d.p).magnitude();
}

inline void RayRadial::rotateZenith(double radians) {
    throw "myFunction is not implemented yet.";
}
inline void RayRadial::rotatePolar(double radians) {
    throw "myFunction is not implemented yet.";
}