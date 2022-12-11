#include "CameraRay3.h"

CameraRay3::CameraRay3(Vector3* position, const Vector3& vector) :
    p(*position),
    v(vector)
{
    /* Ray:
     * x = p.x + v.xt
     * y = p.y + v.yt
     * z = p.z + v.zt
     * t >= 0
     *
     * v ∥ Ray
     * p is a solution of the ray
     */
}
CameraRay3::CameraRay3(Vector3* position, const Vector3s& vector) :
    p(*position),
    v(vector.asRectangular())
{ }

inline void CameraRay3::rotateX(double radians) {
    v.rotateX(radians);
}
inline void CameraRay3::rotateY(double radians) {
    v.rotateY(radians);
}
inline void CameraRay3::rotateZ(double radians) {
    v.rotateZ(radians);
}
inline void CameraRay3::rotate(double r1, double r2, double r3) {
    v.rotate(r1, r2, r3);
}
inline void CameraRay3::rotateAbout(const Vector3& rotand, double radians) {
    v.rotateAbout(rotand, radians);
}

std::ostream& operator<<(std::ostream& stream, const CameraRay3& rhs) {
    return stream << "{ p: " << rhs.p << ", v: " << rhs.v << " }";
}