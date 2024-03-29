﻿#include "Vector3s.h"
#include "Math.h"

Vector3s::Vector3s(double rho, double phi, double theta) :
    rho(rho),
    phi(Math::dmod(phi, PI)),
    theta(Math::dmod(theta, TWO_PI))
{
    /* Spherical Coordinates:
     * ρ = |OP|
     * ϕ = Angle between e3 and OP
     * θ = Polar angle
     *
     * ρ = sqrt(x^2 + y^2 + z^2)
     * cot(ϕ) = y/r
     * ϕ = arccot(y / sqrt(x^2 + z^2))
     * θ = arctan(x/z)
     *
     * Natural Range = NR = [0, ∞) x [0, π] x [0, 2π]
     */

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
Vector3s::Vector3s(const Vector3& rectangular) :
    rho(rectangular.magnitude()),
    phi(Math::acot(rectangular.y / sqrt(rectangular.x * rectangular.x + rectangular.z * rectangular.z))),
    theta(Math::atan(rectangular.x / rectangular.z))
{
    /* Rectangular coordinates to Spherical:
     * ρ = |OP|
     * ϕ = Angle between e3 and OP
     * θ = Polar angle
     *
     * ρ = sqrt(x^2 + y^2 + z^2)
     * cot(ϕ) = y/r
     * ϕ = arccot(y / sqrt(x^2 + z^2))
     * θ = arctan(x/z)
     */
}

Vector3 Vector3s::asRectangular() const {
    Vector3 newVec(*this);
    return newVec;
}


void Vector3s::rotateZenith(double radians) {
    phi += radians;
}
void Vector3s::rotatePolar(double radians) {
    theta += radians;
}
Vector3s Vector3s::rotatedZenith(double radians) const {
    Vector3s newVec(rho, phi + radians, theta);
    return newVec;
}
Vector3s Vector3s::rotatedPolar(double radians) const {
    Vector3s newVec(rho, phi, theta + radians);
    return newVec;
}

template <typename iter>
void rotateZenith(iter begin, iter end, double radians) {
    while (begin != end) {
        begin->rotateZenith(radians);
        ++begin;
    }
}
template <typename iter>
void rotatePolar(iter begin, iter end, double radians) {
    while (begin != end) {
        begin->rotatePolar(radians);
        ++begin;
    }
}
template <typename iter, typename d_iter>
void rotatedZenith(iter begin, iter end, d_iter dest, double radians) {
    while (begin != end) {
        *dest = begin->rotatedZenith(radians);
        ++begin;
    }
}
template <typename iter, typename d_iter>
void rotatedPolar(iter begin, iter end, d_iter dest, double radians) {
    while (begin != end) {
        *dest = begin->rotatedPolar(radians);
        ++begin;
    }
}

Vector3s Vector3s::min(const Vector3s& a, const Vector3s& b) {
    double phiDiff = Math::abs(a.phi - b.phi);
    double thetaDiff = Math::abs(a.theta - b.theta);
    if (phiDiff > HALF_PI)
        phiDiff = PI - phiDiff;
    if (thetaDiff > PI)
        thetaDiff = TWO_PI - thetaDiff;

    return Vector3s(1.0, phiDiff, thetaDiff);
}
Vector3s Vector3s::fromRandom(const Vector3s& min, const Vector3s& max) {
    return Vector3s(Math::random(min.rho, max.rho), Math::random(min.phi, max.phi), Math::random(min.theta, max.theta));
}

std::ostream& operator<<(std::ostream& stream, const Vector3s& rhs) {
    return stream << "{ ρ: " << rhs.rho << ", ϕ: " << rhs.phi << ", θ: " << rhs.theta << " }";
}