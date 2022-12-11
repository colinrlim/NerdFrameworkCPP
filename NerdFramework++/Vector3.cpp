#include <vector>
#include "Vector3.h"
#include "Math.h"

Vector3::Vector3(double x, double y, double z) : x(x), y(y), z(z) { }
Vector3::Vector3(double s) : x(s), y(s), z(s) { }
Vector3::Vector3(const Vector3& a, const Vector3& b) : x(b.x - a.x), y(b.y - a.y), z(b.z - a.z) { }
Vector3::Vector3(const Vector3s& spherical) :
    z(spherical.rho* sin(spherical.phi)* cos(spherical.theta)),
    x(spherical.rho* sin(spherical.phi)* sin(spherical.theta)),
    y(spherical.rho* cos(spherical.phi))
{
    /* Spherical coordinates to Rectangular:
     * x = ρsin(ϕ)cos(θ)
     * y = ρsin(ϕ)sin(θ)
     * z = ρcos(ϕ)
     *
     * HOWEVER: This engine uses x and z as horizontal plane
     * We will shift the values with cyclic permutation
     *
     * z = ρsin(ϕ)cos(θ)
     * x = ρsin(ϕ)sin(θ)
     * y = ρcos(ϕ)
     */
}
Vector3::Vector3(const Vector2& twodim) : x(twodim.x), y(twodim.y), z(0.0) { }

inline Vector3s Vector3::asSpherical() const {
    Vector3s newVec(*this);
    return newVec;
}

const Vector3 Vector3::zero(0.0, 0.0, 0.0);
const Vector3 Vector3::one(1.0, 1.0, 1.0);
const Vector3 Vector3::xAxis(1.0, 0.0, 0.0);
const Vector3 Vector3::yAxis(0.0, 1.0, 0.0);
const Vector3 Vector3::zAxis(0.0, 0.0, 1.0);

inline double Vector3::magnitude() const {

    /* a⋅b = |a||b|cos(theta)
     * a⋅a = |a||a|cos(0) = |a||a|
     * |a| = sqrt(a⋅a)
     */

    return Math::sqrt(Vector3::dot(*this, *this));
}
inline Vector3 Vector3::normalized() const {
    return *this / this->magnitude();
}
inline Vector3 Vector3::normalizedCubic() const {
    double max = Math::max(std::vector<double>{Math::abs(this->x), Math::abs(this->y), Math::abs(this->z)});
    return *this / max;
}

inline void Vector3::rotateX(double radians) {

    /* x' = x
     * y' = ycos(theta) - zsin(theta)
     * z' = ysin(theta) + zcos(theta)
     */

    double s = Math::sin(radians);
    double c = Math::cos(radians);

    // x = x;
    y = y * c - z * s;
    z = y * s + z * c;
}
inline void Vector3::rotateY(double radians) {

    /* x' = xcos(theta) + zsin(theta)
     * y' = y
     * z' = -xsin(theta) + zcos(theta)
     */

    double s = Math::sin(radians);
    double c = Math::cos(radians);

    x = x * c + z * s;
    // y = y;
    z = -x * s + z * c;
}
inline void Vector3::rotateZ(double radians) {

    /* x' = xcos(theta) - ysin(theta)
     * y' = xsin(theta) + ycos(theta)
     * z' = z
     */

    double s = Math::sin(radians);
    double c = Math::cos(radians);

    x = x * c - y * s;
    y = x * s + y * c;
    // z = z;
}
inline void Vector3::rotate(double r1, double r2, double r3) {
    if (r1 != 0.0)
        rotateX(r1);
    if (r2 != 0.0)
        rotateY(r2);
    if (r3 != 0.0)
        rotateZ(r3);
}
inline void Vector3::rotateAbout(const Vector3& rotand, double radians) {
    throw "Not implemented yet";
}

inline Vector3 Vector3::rotatedX(double radians) const {
    Vector3 newVec(*this);
    newVec.rotateX(radians);
    return newVec;
}
inline Vector3 Vector3::rotatedY(double radians) const {
    Vector3 newVec(*this);
    newVec.rotateY(radians);
    return newVec;
}
inline Vector3 Vector3::rotatedZ(double radians) const {
    Vector3 newVec(*this);
    newVec.rotateZ(radians);
    return newVec;
}
inline Vector3 Vector3::rotated(double r1, double r2, double r3) const {
    Vector3 newVec(*this);
    newVec.rotate(r1, r2, r3);
    return newVec;
}
inline Vector3 Vector3::rotatedAbout(const Vector3& rotand, double radians) const {
    Vector3 newVec(*this);
    newVec.rotateAbout(rotand, radians);
    return newVec;
}

inline Vector3 Vector3::angle3(const Vector3& a, const Vector3& b) {
    // Create projections of vectors a and b onto the x-axis
    Vector3 Ax = Vector3(0.0, a.y, a.z);
    Vector3 Bx = Vector3(0.0, b.y, b.z);

    // Calculate 2D x-angle between projections
    double xRadians = Vector3::angle(Ax, Bx);

    // Create angle-adjusted a vector
    Vector3 a2 = a.rotatedX(xRadians);

    // Create projections of vectors a2 and b onto the y-axis
    Vector3 Ay = Vector3(a2.x, 0.0, a2.z);
    Vector3 By = Vector3(b.x, 0.0, b.z);

    // Calculate 2D y-angle between projections
    double yRadians = Vector3::angle(Ay, By);

    // Create angle-adjusted a vector
    Vector3 a3 = a2.rotatedY(yRadians);

    // Create projections of vectors a3 and b onto the z-axis
    Vector3 Az = Vector3(a3.x, a3.y, 0.0);
    Vector3 Bz = Vector3(b.x, b.y, 0.0);

    // Calculate 2D z-angle between projections
    double zRadians = Vector3::angle(Az, Bz);

    Vector3 newVec(xRadians, yRadians, zRadians);
    return newVec;
}
inline double Vector3::angle(const Vector3& a, const Vector3& b) {

    /* a⋅b = |a||b|cos(theta)
     *
     * cos(theta) = (a⋅b)/(|a||b|)
     * theta = acos((a⋅b)/(|a||b|))
     */

    if (a == b)
        return 0.0;
    return Math::acos(Vector3::dot(a, b) / (a.magnitude() * b.magnitude()));
}
inline double Vector3::dot(const Vector3& a, const Vector3& b) {

    /* a⋅b = (a1*b1) + (a2*b2) + (a3*b3)
     *
     * a⋅b = 0 <=> a ⊥ b
     *
     * a⋅b = 1 <=> a'⋅b = 0 <=> a' ⊥ b
     *
     * a⋅b = |a||b|cos(theta)
     *
     * a⋅b = b⋅a
     */

    return (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
}
inline Vector3 Vector3::cross(const Vector3& a, const Vector3& b) {

    /*          | e1 e2 e3 |      | a2 a3 |        | a1 a3 |        | a1 a2 |
     * a×b = det| a1 a2 a3 | = det| b2 b3 |e1 - det| b1 b3 |e2 + det| b1 b2 |e3
     *          | b1 b2 b3 |
     *
     *  = <(a2*b3) - (a3*b2), -[(a1*b3) - (a3*b1)], (a1*b2) - (a2*b1)>
     *
     * c = a×b <=> c ⊥ a AND c ⊥ b
     *
     * |a×b| = |A||B|sin(theta) = Area of Parallelogram
     *
     * a×b = -b×a
     */

    Vector3 newVec((a.y * b.z) - (a.z * b.y), -(a.x * b.z) + (a.z * b.x), (a.x * b.y) - (a.y * b.x));
    return newVec;
}
inline double Vector3::triple(const Vector3& a, const Vector3& b, const Vector3& c) {

    /*              | a1 a2 a3 |      | b2 b3 |        | b1 b3 |        | b1 b2 |
     * a⋅(b×c) = det| b1 b2 b3 | = det| c2 c3 |a1 - det| c1 c3 |a2 + det| c1 c2 |a3
     *              | c1 c2 c3 |
     *
     *  = [(b2*c3) - (b3*c2)]a1 -[(b1*c3) - (b3*c1)]a2 + [(b1*c2) - (b2*c1)]a3
     *
     * |a⋅(b×c)| = Volume of Parallelepiped
     *
     * a⋅(b×c) = c⋅(a×b) = b⋅(c×a)
     * a⋅(b×c) = -b⋅(a×c) = -c⋅(b×a)
     */

    return ((b.y * c.z) - (b.z * c.y)) * a.x - ((b.x * c.z) - (b.z * c.x)) * a.y + ((b.x * c.y) - (b.y * c.x)) * a.z;
}
inline bool Vector3::parallel(const Vector3& a, const Vector3& b) {

    /* IF a = b * s:
     * a ∥ b
     *
     * CANNOT check if a/s = b,
     * as a component of s COULD be zero
     */

    Vector3 v1 = a.normalized();
    Vector3 v2 = b.normalized();
    return (v1 == v2 || v1 == -v2);
}
inline Vector3 Vector3::lerp(const Vector3& a, const Vector3& b, double alpha) {
    return a * (1 - alpha) + b * alpha;
}
inline Vector3 Vector3::fromParameterization3(double t, double s, const Vector3& a, const Vector3& b, const Vector3& c) {
    double u = 1.0 - t - s;
    Vector3 newVec(a.x * u + b.x * t + c.x * s, a.y * u + b.y * t + c.y * s, a.z * u + b.z * t + c.z * s);
    return newVec;
}

Vector3& Vector3::operator+=(const Vector3& rhs) {
    this->x += rhs.x;
    this->y += rhs.y;
    this->z += rhs.z;
    return *this;
}
Vector3& Vector3::operator+=(double rhs) {
    this->x += rhs;
    this->y += rhs;
    this->z += rhs;
    return *this;
}
Vector3 Vector3::operator+(const Vector3& rhs) const {
    Vector3 newVec(this->x + rhs.x, this->y + rhs.y, this->z + rhs.z);
    return newVec;
}
Vector3 Vector3::operator+(double rhs) const {
    Vector3 newVec(this->x + rhs, this->y + rhs, this->z + rhs);
    return newVec;
}
Vector3& Vector3::operator-=(const Vector3& rhs) {
    this->x -= rhs.x;
    this->y -= rhs.y;
    this->z -= rhs.z;
    return *this;
}
Vector3& Vector3::operator-=(double rhs) {
    this->x -= rhs;
    this->y -= rhs;
    this->z -= rhs;
    return *this;
}
Vector3 Vector3::operator-(const Vector3& rhs) const {
    Vector3 newVec(this->x - rhs.x, this->y - rhs.y, this->z - rhs.z);
    return newVec;
}
Vector3 Vector3::operator-(double rhs) const {
    Vector3 newVec(this->x - rhs, this->y - rhs, this->z - rhs);
    return newVec;
}
Vector3 Vector3::operator-() const {
    Vector3 newVec(-this->x, -this->y, -this->z);
    return newVec;
}
Vector3& Vector3::operator*=(const Vector3& rhs) {
    this->x *= rhs.x;
    this->y *= rhs.y;
    this->z *= rhs.z;
    return *this;
}
Vector3& Vector3::operator*=(double rhs) {
    this->x *= rhs;
    this->y *= rhs;
    this->z *= rhs;
    return *this;
}
Vector3 Vector3::operator*(const Vector3& rhs) const {
    Vector3 newVec(this->x * rhs.x, this->y * rhs.y, this->z * rhs.z);
    return newVec;
}
Vector3 Vector3::operator*(double rhs) const {
    Vector3 newVec(this->x * rhs, this->y * rhs, this->z * rhs);
    return newVec;
}
Vector3& Vector3::operator/=(const Vector3& rhs) {
    this->x /= rhs.x;
    this->y /= rhs.y;
    this->z /= rhs.z;
    return *this;
}
Vector3& Vector3::operator/=(double rhs) {
    this->x /= rhs;
    this->y /= rhs;
    this->z /= rhs;
    return *this;
}
Vector3 Vector3::operator/(const Vector3& rhs) const {
    Vector3 newVec(this->x / rhs.x, this->y / rhs.y, this->z / rhs.z);
    return newVec;
}
Vector3 Vector3::operator/(double rhs) const {
    Vector3 newVec(this->x / rhs, this->y / rhs, this->z / rhs);
    return newVec;
}

bool Vector3::operator==(const Vector3& rhs) const {
    return (*this - rhs).magnitude() <= 0.00001;
}
bool Vector3::operator!=(const Vector3& rhs) const {
    return (*this - rhs).magnitude() > 0.00001;
}

std::ostream& operator<<(std::ostream& stream, const Vector3& rhs) {
    return stream << "{ " << rhs.x << ", " << rhs.y << ", " << rhs.z << " }";
}