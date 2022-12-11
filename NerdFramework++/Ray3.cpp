#include "Ray3.h"

Ray3::Ray3(const Vector3& position, const Vector3& vector) :
    p(p),
    v(v)
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
Ray3::Ray3(const Vector3& position, const Vector3s& vector) :
    p(p),
    v(vector.asRectangular())
{ }

inline Ray3 Ray3::lerp(const Ray3& a, const Ray3& b, double alpha) {
    return a * (1 - alpha) + b * alpha;
}

inline void Ray3::rotateX(double radians) {
    v.rotateX(radians);
}
inline void Ray3::rotateY(double radians) {
    v.rotateY(radians);
}
inline void Ray3::rotateZ(double radians) {
    v.rotateZ(radians);
}
inline void Ray3::rotate(double r1, double r2, double r3) {
    v.rotate(r1, r2, r3);
}
inline void Ray3::rotateAbout(const Vector3& rotand, double radians) {
    v.rotateAbout(rotand, radians);
}

Ray3 Ray3::operator+(const Ray3& rhs) const {
    return Ray3(this->p + rhs.p, this->v + rhs.v);
}
Ray3 Ray3::operator-(const Ray3& rhs) const {
    return Ray3(this->p - rhs.p, this->v - rhs.v);
}
Ray3 Ray3::operator*(const Ray3& rhs) const {
    return Ray3(this->p * rhs.p, this->v * rhs.v);
}
Ray3 Ray3::operator*(double rhs) const {
    return Ray3(this->p * rhs, this->v * rhs);
}
Ray3 Ray3::operator/(const Ray3& rhs) const {
    return Ray3(this->p / rhs.p, this->v / rhs.v);
}
Ray3 Ray3::operator/(double rhs) const {
    return Ray3(this->p / rhs, this->v / rhs);
}

bool Ray3::operator==(const Ray3& rhs) const {
    return this->p == rhs.p && this->v == rhs.v;
}
bool Ray3::operator!=(const Ray3& rhs) const {
    return this->p != rhs.p || this->v != rhs.v;
}

std::ostream& operator<<(std::ostream& stream, const Ray3& rhs) {
    return stream << "{ p: " << rhs.p << ", v: " << rhs.v << " }";
}