#include "RayCaster.h"

void RayCaster::rotateX(double radians) {
    d.rotateX(radians);
    w.rotateX(radians);
    h.rotateX(radians);
}
void RayCaster::rotateY(double radians) {
    d.rotateY(radians);
    w.rotateY(radians);
    h.rotateY(radians);
}
void RayCaster::rotateZ(double radians) {
    d.rotateZ(radians);
    w.rotateZ(radians);
    h.rotateZ(radians);
}
void RayCaster::rotate(double r1, double r2, double r3) {
    d.rotate(r1, r2, r3);
    w.rotate(r1, r2, r3);
    h.rotate(r1, r2, r3);
}
void RayCaster::rotateTo(const Vector3& vector) {
    Vector3 rotation = Vector3::angle3(d.v, vector);
    rotate(rotation.x, rotation.y, rotation.z);
}
void RayCaster::rotateAbout(const Vector3& rotand, double radians) {
    d.rotateAbout(rotand, radians);
    w.rotatedAbout(rotand, radians);
    h.rotatedAbout(rotand, radians);
}