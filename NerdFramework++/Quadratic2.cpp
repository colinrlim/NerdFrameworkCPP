#include "Quadratic2.h"
#include "Math.h"

Quadratic2::Quadratic2(double a, double b, double c, double d, double e, double f) :
	a(a),
	b(b),
	c(c),
	d(d),
	e(e),
	f(f)
{ }

double Quadratic2::equals(double x, double y) {
	return a * x * x + b * y * y + c * x * y + d * x + e * y + f;
}

void Quadratic2::rotate(double radians) {

    /* x' = xcos(theta) - ysin(theta)
     * y' = xsin(theta) + ycos(theta)
     *
     * Ax^2 + By^2 + Cxy + Dx + Ey + F
     *
     * s = sin(theta)
     * c = cos(theta)
     *
     * Ax'^2 + By'^2 + Cx'y' + Dx' + Ey' + F
     * A(xc - ys)^2 + B(xs + yc)^2 + C(xc - ys)(xs + yc) + D(xc - ys) + E(xs + yc) + F
     * Accx^2 - 2Acsxy + Assy^2 + Bssx^2 + 2Bscxy + Bccy^2 + Ccsx^2 + Cccxy - Cssyx - Cscy^2 + Dcx - Dsy + Esx + Ecy + F
     * (Acc+Bss+Ccs)x^2 + (Ass+Bcc-Csc)y^2 + (2Bsc+Ccc-2Acs-Css)xy + (Dc+Es)x + (Ec-Ds)y + F
     * A' = (Acc+Bss+Ccs)
     * B' = (Ass+Bcc-Csc)
     * C' = (2Bsc+Ccc-2Acs-Css)
     * D' = (Dc+Es)
     * E' = (Ec-Ds)
     * F' = (F)
     */

    double s_ = Math::sin(radians);
    double c_ = Math::cos(radians);
    double ss_ = s_ * s_;
    double sc_ = s_ * c_;
    double cc_ = 1.0 - ss_;

    double A = (a * cc_ + b * ss_ + c * sc_);
    double B = (a * ss_ + b * cc_ - c * sc_);
    double C = (2 * (b - a) * sc_ + c * cc_ - c * ss_);
    double D = (d * c_ + e * s_);
    double E = (e * c_ - d * s_);
    double F = (f);

    this->a = A;
    this->b = B;
    this->c = C;
    this->d = D;
    this->e = E;
    this->f = F;
}

std::ostream& operator<<(std::ostream& stream, const Quadratic2& rhs) {
    return stream << rhs.a << "x^2 + " << rhs.b << "y^2 + " << rhs.c << "xy + " << rhs.d << "x + " << rhs.e << "y + " << rhs.f;
}