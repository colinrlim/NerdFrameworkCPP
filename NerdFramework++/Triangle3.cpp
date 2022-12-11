#include "Triangle3.h"
#include "Plane3.h"
#include "Line3.h"
struct Plane3;
struct Line3;

Triangle3::Triangle3(Vector3* a, Vector3* b, Vector3* c) :
    a(*a),
    b(*b),
    c(*c)
{
    /* Triangle:
     * a: point1
     * b: point2
     * c: point3
     */
}

inline Vector3 Triangle3::normal() const {

    /* A, B, and C are COPLANAR, all are solutions of Plane in which triangle resides
     * n ⊥ Plane
     *
     * n ⊥ A, B, and C
     * n ⊥ AB and AC
     *
     * c ⊥ a AND c ⊥ b <=> c = a×b
     * n = a×b
     */

    return Vector3::cross(Vector3(a, b), Vector3(a, c));
}
inline double Triangle3::area() const {

    /* |a×b| = |A||B|sin(theta) = Area of Parallelogram
     * Parallelogram is two triangles
     */

    return Vector3::cross(b - a, c - a).magnitude() / 2.0;
}

inline void Triangle3::move(const Vector3& offset) {
    a += offset;
    b += offset;
    c += offset;
}
inline void Triangle3::scale(const Vector3& scale, const Vector3& origin) {
    a -= origin;
    b -= origin;
    c -= origin;

    a *= scale;
    b *= scale;
    c *= scale;

    a += origin;
    b += origin;
    c += origin;
}

inline void Triangle3::rotateX(double radians, const Vector3& origin) const {
    a -= origin;
    b -= origin;
    c -= origin;

    a.rotateX(radians);
    b.rotateX(radians);
    c.rotateX(radians);

    a += origin;
    b += origin;
    c += origin;
}
inline void Triangle3::rotateY(double radians, const Vector3& origin) const {
    a -= origin;
    b -= origin;
    c -= origin;

    a.rotateY(radians);
    b.rotateY(radians);
    c.rotateY(radians);

    a += origin;
    b += origin;
    c += origin;
}
inline void Triangle3::rotateZ(double radians, const Vector3& origin) const {
    a -= origin;
    b -= origin;
    c -= origin;

    a.rotateZ(radians);
    b.rotateZ(radians);
    c.rotateZ(radians);

    a += origin;
    b += origin;
    c += origin;
}
inline void Triangle3::rotate(double r1, double r2, double r3, const Vector3& origin) const {
    a -= origin;
    b -= origin;
    c -= origin;

    a.rotate(r1, r2, r3);
    b.rotate(r1, r2, r3);
    c.rotate(r1, r2, r3);

    a += origin;
    b += origin;
    c += origin;
}

inline Vector2 Triangle3::parameterization(const Vector3& a, const Vector3& b, const Vector3& c, const Vector3& point) {

    // Repackages the Parameterization(Point) method for single use

    Vector3 AB = b - a;
    Vector3 AC = c - a;
    Vector3 AP = point - a;
    double ABdiff = AB.x / AB.y;
    double ACdiff = AC.x / AC.y;
    double t = (AP.x - AP.y * ACdiff) / (AB.x - AB.y * ACdiff);
    double s = (AP.x - AP.y * ABdiff) / (AC.x - AC.y * ABdiff);

    Vector2 params(t, s);
    return params;
}
inline Vector2 Triangle3::parameterization(const Vector3& point) const {

    // Repackages the Meets(Point) method to spit out t and s
    // Useful for any operations that involve finding a vector
    // in terms of two non-parallel vector components

    /* A, B, and C are COPLANAR, and vertices of the triangle
     * P is any point that lies within the triangle
     *
     * Parameterization of triangle:
     * A triangle is created by two vectors AB and AC
     * A solution of the triangle consists of initial point A with added components AB*t and AC*s
     * In other words, picture a triangle as a defined coordinate plane of two (non?)orthogonal axes, AB and AC
     *
     * OP = OA + (OB-OA)t + (OC-OA)s
     * (OP-OA) = (OB-OA)t + (OC-OA)s <=> AP = ABt + ACs
     * The point is within the triangle if t and s fall within defined boundaries
     *
     * Solving for t and s:
     * P = (OP-OA)
     * B = (OB-OA)
     * C = (OC-OA)
     *
     * P = Bt + Cs
     * Since P being coplanar is a given, we can eliminate one dimension through rotation (rigid transformation)
     * Thus, we can derive t and s from a system of two equations:
     * P.x = B.x*t + C.x*s
     * P.y = B.y*t + C.y*s
     *
     * s = (P.y - B.y*t)/C.y
     * t = (P.y - C.y*s)/B.y
     *
     * P.x = B.x*t + C.x*[(P.y - B.y*t)/C.y]
     * B.x*t - B.y*t*(C.x/C.y) = P.x - P.y*(C.x/C.y)
     * t = [P.x - P.y*(C.x/C.y)] / [B.x - B.y*(C.x/C.y)]
     *
     * P.x = B.x*(P.y - C.y*s)/B.y + C.x*s
     * C.x*s - C.y*s*(B.x/B.y) = P.x - P.y*(B.x/B.y)
     * s = [P.x - P.y*(B.x/B.y)] / [C.x - C.y*(B.x/B.y)]
     *
     * t and s are interpolant values between 0 and 1 that describe P length relative to axis lengths
     * IF t defines how far the point is along AB and s the same for AC:
     * The hypotenuse BC can be seen as a linear inverse relationship between s and t
     *
     * THUS the additional condition applies:
     * t <= 1 - s
     * t + s <= 1
     *
     * [Conclusion]
     * After calculating t and s using the following formulas:
     * t = [P.x - P.y*(C.x/C.y)] / [B.x - B.y*(C.x/C.y)]
     * s = [P.x - P.y*(B.x/B.y)] / [C.x - C.y*(B.x/B.y)]
     */

    Vector3 AB = b - a;
    Vector3 AC = c - a;
    Vector3 AP = point - a;
    double ABdiff = AB.x / AB.y;
    double ACdiff = AC.x / AC.y;
    double t = (AP.x - AP.y * ACdiff) / (AB.x - AB.y * ACdiff);
    double s = (AP.x - AP.y * ABdiff) / (AC.x - AC.y * ABdiff);

    Vector2 params(t, s);
    return params;
}

inline bool Triangle3::meets(const Vector3& point) const {

    /* A, B, and C are COPLANAR, and vertices of the triangle
     * P is any point that lies within the triangle
     *
     * Parameterization of triangle:
     * A triangle is created by two vectors AB and AC
     * A solution of the triangle consists of initial point A with added components AB*t and AC*s
     * In other words, picture a triangle as a defined coordinate plane of two (non?)orthogonal axes, AB and AC
     *
     * OP = OA + (OB-OA)t + (OC-OA)s
     * (OP-OA) = (OB-OA)t + (OC-OA)s <=> AP = ABt + ACs
     * The point is within the triangle if t and s fall within defined boundaries
     *
     * Solving for t and s:
     * P = (OP-OA)
     * B = (OB-OA)
     * C = (OC-OA)
     *
     * P = Bt + Cs
     * Since P being coplanar is a given, we can eliminate one dimension through rotation (rigid transformation)
     * Thus, we can derive t and s from a system of two equations:
     * P.x = B.x*t + C.x*s
     * P.y = B.y*t + C.y*s
     *
     * s = (P.y - B.y*t)/C.y
     * t = (P.y - C.y*s)/B.y
     *
     * P.x = B.x*t + C.x*[(P.y - B.y*t)/C.y]
     * B.x*t - B.y*t*(C.x/C.y) = P.x - P.y*(C.x/C.y)
     * t = [P.x - P.y*(C.x/C.y)] / [B.x - B.y*(C.x/C.y)]
     *
     * P.x = B.x*(P.y - C.y*s)/B.y + C.x*s
     * C.x*s - C.y*s*(B.x/B.y) = P.x - P.y*(B.x/B.y)
     * s = [P.x - P.y*(B.x/B.y)] / [C.x - C.y*(B.x/B.y)]
     *
     * t and s are interpolant values between 0 and 1 that describe P length relative to axis lengths
     * IF t defines how far the point is along AB and s the same for AC:
     * The hypotenuse BC can be seen as a linear inverse relationship between s and t
     *
     * THUS the additional condition applies:
     * t <= 1 - s
     * t + s <= 1
     *
     * [Conclusion]
     * After calculating t and s using the following formulas:
     * t = [P.x - P.y*(C.x/C.y)] / [B.x - B.y*(C.x/C.y)]
     * s = [P.x - P.y*(B.x/B.y)] / [C.x - C.y*(B.x/B.y)]
     *
     * The point is a solution of the triangle if:
     * t >= 0
     * s >= 0
     * t + s <= 1
     */

    Vector3 AB = b - a;
    Vector3 AC = c - a;
    Vector3 AP = point - a;
    double ABdiff = AB.x / AB.y;
    double ACdiff = AC.x / AC.y;
    double t = (AP.x - AP.y * ACdiff) / (AB.x - AB.y * ACdiff);
    double s = (AP.x - AP.y * ABdiff) / (AC.x - AC.y * ABdiff);

    return t >= 0.0 && s >= 0.0 && t + s <= 1.0;


    /* METHOD 2 [Less optimized] */

     /* A, B, and C are COPLANAR, all are solutions of Plane
     *
     * p1 lies between AB and AC IF:
     *
     * Angles AB-AP and AC-AP equal AB-AC:
     * a⋅b = |a||b|cos(theta)
     * cos(theta) = (a⋅b)/(|a||b|)
     * theta = acos((a⋅b)/(|a||b|))
     * acos((AB⋅AP)/(|AB||AP|)) + acos((AC⋅AP)/(|AC||AP|)) <= acos((AB⋅AC)/(|AB||AC|))
     * acos((AB⋅AP)/(|AB||AP|)) + acos((AC⋅AP)/(|AC||AP|)) <= acos((AB⋅AC)/(|AB||AC|))
     *
     * Magnitude of the projection of AP onto AB and AC is <= the magnitude of AB and AC:
     * a⋅b = |a||b|cos(theta)
     * AB⋅AP = |AB||AP|cos(theta)
     * |AP|cos(theta) = AB⋅AP/|AB|
     * AB⋅AP/|AB| <= |AB|
     * AB⋅AP <= |AB||AB|
     * AB⋅AP <= AB⋅AB
     * AC⋅AP <= AC⋅AC
     */

     /*Vector3 AB = (b - a);
     Vector3 AC = (c - a);
     Vector3 AP = (point - a);
     double ABm = AB.Magnitude();
     double ACm = AC.Magnitude();
     double APm = AP.Magnitude();
     double ABAP = Vector3.Dot(AB, AP);
     double ACAP = Vector3.Dot(AC, AP);

     return
         Math.Abs(Math.Acos(Vector3.Dot(AB, AC) / (ABm * ACm)) - (Math.Acos(ABAP / (ABm * APm)) + Math.Acos(ACAP / (ACm * APm)))) <= 0.0001 &&
         ABAP <= ABm * ABm && ACAP <= ACm * ACm;*/
}
inline bool Triangle3::meets(const Ray3& ray) const {

    /* 1st Check:
     * Would the ray collide on the triangle's front face?
     */

    if (Vector3::dot(ray.v, this->normal()) >= 0.0) return false;

    /* 2nd Check:
     * Simplifies the question in terms of the line the ray resides in and the plane the triangle resides in
     * Do they meet?
     */

     /* I'm actually gonna comment out this check for the sake of optimization.
      * Put on your tinfoil hat and hear me out here.
      * All this step really does is check and make sure that the ray and triangle aren't parallel.
      * However, since the Vector3's are made of doubles, PERFECTLY PARALLEL vectors are almost impossible.
      * Eg.) Vectors are likely to math out to be at least 0.00001 degrees away from perfectly parallel.
      * Commenting this out will introduce an unchecked edge case, but one that is very very unlikely to exist.
      *
      * To *kinda* check for it, I'm changing the ">" in the 1st check to ">=" to weed out perfectly parallel cases.
      * The consequence is that this function won't really work for perfectly parallel cases,
      * but to the benefit of an extremely small performance uplift.
      */

      //Vector3 n = Normal();
      //Line3 line = new Line3(ray.p, ray.v);
      //Plane3 plane = new Plane3(a, n);
      //if (!plane.Meets(line)) return false;

      /* Final Check:
       * Is this point of intersection within the triangle?
       */

       /* Plane:
        * n.x(x - q.x) + n.y(y - q.y) + n.z(z - q.z) = 0
        *
        * Line:
        * x = p.x + v.xt
        * y = p.y + v.yt
        * z = p.z + v.zt
        *
        * Intersection:
        * n.x([p.x + v.xt] - q.x) + n.y([p.y + v.yt] - q.y) + n.z([p.z + v.zt] - q.z) = 0
        * n⋅p + n⋅vt - n⋅q = 0
        * (n⋅v)t = n⋅(q - p)
        * t = [n⋅(q - p)]/(n⋅v)
        */

    Vector3 pointOfIntersection = this->intersection(ray); //plane.Intersection(line);

    //if (Vector3.Dot((pointOfIntersection - line.p), line.v) < 0) return false;
    //if ((pointOfIntersection - line.p).Normalized() != line.v.Normalized()) return false;

    return this->meets(pointOfIntersection);
}
/*bool meets(Triangle3 triangle);*/

inline Vector3* Triangle3::ifMeetsGetIntersection(const Ray3& ray) const {

    /* Repackages the Meets(Ray) method to return the intersection
     * for optimization purposes where you'd need the intersection for a secondary operation.
     */

    if (Vector3::dot(ray.v, this->normal()) >= 0.0) return nullptr;

    Vector3* pointOfIntersection = new Vector3(intersection(ray));

    if (this->meets(*pointOfIntersection))
        return pointOfIntersection;
    return nullptr;
}
inline Vector3 Triangle3::intersection(const Ray3& ray) const {

    // In order to maximize performance, this code assumes you will only
    //   use this function if you already know the triangle and ray intersect at a point.
    // This condition can be checked for by using the Meets(Ray) function.

    Line3 line(ray.p, ray.v);
    Plane3 plane(this->a, this->normal());

    return plane.intersection(line);
}

std::ostream& operator<<(std::ostream& stream, const Triangle3& rhs) {
    return stream << "{ a: " << rhs.a << ", b: " << rhs.b << ", c: " << rhs.c << " }";
}