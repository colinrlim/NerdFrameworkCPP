#include "RayRectangular.h"
#include "Plane3.h"

RayRectangular::RayRectangular(const CameraRay3& direction, double width, double height) :
    RayCaster(direction, Vector3::xAxis* width, Vector3::yAxis* height)
{
    this->d.v = Vector3::zAxis;
	
	this->rotateTo(direction.v);
}

Ray3 RayRectangular::rayAt(double wAlpha, double hAlpha) {
	Vector3 position = d.p + w * (wAlpha - 0.5) + h * (hAlpha - 0.5);
	return Ray3(position, d.v);
}
Vector3 RayRectangular::vectorAt(double wAlpha, double hAlpha) {
	return d.v;
}
Vector2 RayRectangular::projection(const Vector3& point) {
    return Vector2(point.x / w.x + 0.5, point.y / h.y + 0.5);

    /* Get projection of point onto camera as intersection of shortest path from point to camera's plane
     *
     * Plane:
     * n.x(x - q.x) + n.y(y - q.y) + n.z(z - q.z) = 0
     *
     * Line:
     * x = p.x + v.xt
     * y = p.y + v.yt
     * z = p.z + v.zt
     *
     * Shortest path is ⊥ to Plane
     * n ⊥ Plane
     *
     * Shortest path ∥ n
     * v = n
     * p = point
     *
     * P0 = Origin of camera
     * w = Horizontal axis vector of camera
     * h = Vertical axis vector of camera
     * P1 = Intersection(plane, line)
     *
     * P1 = P0 + wt + hs
     * We can eliminate one dimension through rotation (rigid transformation)
     * Thus, we can derive t and s from a system of two equations:
     * P1.x = P0.x + w.x*t + h.x*s
     * P1.y = P0.y + w.y*t + h.y*s
     *
     * t = (P1.y - P0.y - h.y*s) / w.y
     * s = (P1.y - P0.y - w.y*t) / h.y
     *
     * P1.x = P0.x + w.x*t + h.x*[(P1.y - P0.y - w.y*t) / h.y]
     * w.x*t - w.y*t*(h.x/h.y) = P1.x + P0.y*(h.x/h.y) - P0.x - P1.y*(h.x/h.y)
     * t = [P1.x + P0.y*(h.x/h.y) - P0.x - P1.y*(h.x/h.y)] / [w.x - w.y*(h.x/h.y)]
     *
     * P1.x = P0.x + w.x*[(P1.y - P0.y - h.y*s) / w.y] + h.x*s
     * h.x*s - h.y*s*(w.x/w.y) = P1.x + P0.y*(w.x/w.y) - P0.x - P1.y*(w.x/w.y)
     * s = [P1.x + P0.y*(w.x/w.y) - P0.x - P1.y*(w.x/w.y)] / [h.x - h.y*(w.x/w.y)]
     *
     * Since the origin is in the center of the screen:
     * t += 0.5
     * s += 0.5
     */

     /*Plane3 plane = new Plane3(d.p, d.v);
     Line3 line = new Line3(point, d.v);

     Vector3 intersection = plane.Intersection(line);

     double hSlope = h.x / h.y;
     double wSlope = w.x / w.y;

     return new Vector2(
         (intersection.x + d.p.y * hSlope - d.p.x - intersection.y * hSlope) / (w.x - w.y * hSlope) + 0.5,
         (intersection.x + d.p.y * wSlope - d.p.x - intersection.y * wSlope) / (h.x - h.y * wSlope) + 0.5
     );*/
}
bool RayRectangular::meets(const Vector3& point) {
    throw "myFunction is not implemented yet.";
}
bool RayRectangular::meets(const Triangle3& triangle) {
    throw "myFunction is not implemented yet.";
}
double RayRectangular::distance(const Vector3& point) {
    Plane3 plane(d.p, d.v);
    return plane.min(point);
}

void RayRectangular::rotateZenith(double radians) {
    throw "myFunction is not implemented yet.";
}
void RayRectangular::rotatePolar(double radians) {
    throw "myFunction is not implemented yet.";
}