#include "RayCaster.h"

inline void RayCaster::rotateX(double radians) {
    d.rotateX(radians);
    w.rotateX(radians);
    h.rotateX(radians);
}
inline void RayCaster::rotateY(double radians) {
    d.rotateY(radians);
    w.rotateY(radians);
    h.rotateY(radians);
}
inline void RayCaster::rotateZ(double radians) {
    d.rotateZ(radians);
    w.rotateZ(radians);
    h.rotateZ(radians);
}
inline void RayCaster::rotate(double r1, double r2, double r3) {
    d.rotate(r1, r2, r3);
    w.rotate(r1, r2, r3);
    h.rotate(r1, r2, r3);
}
inline void RayCaster::rotateTo(const Vector3& vector) {
    Vector3 rotation = Vector3::angle3(d.v, vector);
    rotate(rotation.x, rotation.y, rotation.z);
}
inline void RayCaster::rotateAbout(const Vector3& rotand, double radians) {
    d.rotateAbout(rotand, radians);
    w.rotatedAbout(rotand, radians);
    h.rotatedAbout(rotand, radians);
}