#include "Quadratic3.h"
#include "Math.h"

Quadratic3::Quadratic3(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j) :
	a(a),
	b(b),
	c(c),
	d(d),
	e(e),
	f(f),
	g(g),
	h(h),
	i(i),
	j(j)
{
	// Ax^2 + By^2 + Cz^2 + Dxy + Exz + Fyz + Gx + Hy + Iz + J
}

double Quadratic3::equals(double x, double y, double z) {
	return a * x * x + b * y * y + c * z * z + d * x * y + e * x * z + f * y * z + g * x + h * y + i * z + j;
}

void Quadratic3::rotateX(double radians) {

    /* x' = x
    * y' = ycos(theta) - zsin(theta)
    * z' = ysin(theta) + zcos(theta)
    *
    * Ax^2 + By^2 + Cz^2 + Dxy + Exz + Fyz + Gx + Hy + Iz + J
    *
    * s = sin(theta)
    * c = cos(theta)
    *
    * Ax'^2 + By'^2 + Cz'^2 + Dx'y' + Ex'z' + Fy'z' + Gx' + Hy' + Iz' + J
    * Ax^2 + B(yc - zs)^2 + C(ys + zc)^2 + Dx(yc - zs) + Ex(ys + zc) + F(yc - zs)(ys + zc) + Gx + H(yc - zs) + I(ys + zc) + J
    * Ax^2 + Bccy^2 - 2Bcsyz + Bssz^2 + Cssy^2 + 2Cscyz + Cccz^2 + Dcxy - Dsxz + Esxy + Ecxz + Fcsy^2 + Fccyz - Fssyz - Fscz^2 + Gx + Hcy - Hsz + Isy + Icz + J
    * (A)x^2 + (Bcc+Fcs+Css)y^2 + (Bss+2Ccc-Fsc)z^2 + (Dc+Es)xy + (Ec-Ds)xz + (Csc+Fcc-2Bcs-Fss)yz + (G)x + (Hc+Is)y + (Ic-Hs)z + J
    * A' = (A)
    * B' = (Bcc+Fcs+Css)
    * C' = (Bss+Ccc-Fsc)
    * D' = (Dc+Es)
    * E' = (Ec-Ds)
    * F' = (2Csc+Fcc-2Bcs-Fss)
    * G' = (G)
    * H' = (Hc+Is)
    * I' = (Ic-Hs)
    * J' = (J)
    */

    double s_ = Math::sin(radians);
    double c_ = Math::cos(radians);

    double ss_ = s_ * s_;
    double sc_ = s_ * c_;
    double cc_ = 1.0 - ss_;

    double A = (a);
    double B = (b * cc_ + f * sc_ + c * ss_);
    double C = (b * ss_ + c * cc_ - f * sc_);
    double D = (d * c_ + e * s_);
    double E = (e * c_ - d * s_);
    double F = (2 * (c - b) * sc_ + f * cc_ - f * ss_);
    double G = (g);
    double H = (h * c_ + i * s_);
    double I = (i * c_ - h * s_);
    double J = (j);

    a = A;
    b = B;
    c = C;
    d = D;
    e = E;
    f = F;
    g = G;
    h = H;
    i = I;
    j = J;
}
void Quadratic3::rotateY(double radians) {

    /* x' = xcos(theta) + zsin(theta)
     * y' = y
     * z' = -xsin(theta) + zcos(theta)
     *
     * Ax^2 + By^2 + Cz^2 + Dxy + Exz + Fyz + Gx + Hy + Iz + J
     *
     * s = sin(theta)
     * c = cos(theta)
     *
     * Ax'^2 + By'^2 + Cz'^2 + Dx'y' + Ex'z' + Fy'z' + Gx' + Hy' + Iz' + J
     * A(xc + zs)^2 + By^2 + C(-xs + zc)^2 + D(xc + zs)y + E(xc + zs)(-xs + zc) + Fy(-xs + zc) + G(xc + zs) + Hy + I(-xs + zc) + J
     * Accx^2 + 2Acsxz + Assz^2 + By^2 + Cssx^2 - 2Cscxz + Cccz^2 + Dcxy + Dsyz - Ecsx^2 + Eccxz - Esszx + Escz^2 - Fsxy + Fcyz + Gcx + Gsz + Hy - Isx + Icz + J
     * (Acc+Css-Ecs)x^2 + (B)y^2 + (Ass+Ccc+Esc)z^2 + (Dc-Fs)xy + (2Acs-2Csc+Ecc-Ess)xz + (Ds+Fc)yz + (Gc-Is)x + (H)y + (Gs+Ic)z + J
     * A' = (Acc+Css-Ecs)
     * B' = (B)
     * C' = (Ass+Ccc+Esc)
     * D' = (Dc-Fs)
     * E' = (2Acs-2Csc+Ecc-Ess)
     * F' = (Ds+Fc)
     * G' = (Gc-Is)
     * H' = (H)
     * I' = (Gs+Ic)
     * J' = (J)
     */

    double s_ = Math::sin(radians);
    double c_ = Math::cos(radians);
    double ss_ = s_ * s_;
    double cc_ = c_ * c_;
    double sc_ = s_ * c_;

    double A = (a * cc_ + c * ss_ - e * sc_);
    double B = (b);
    double C = (a * ss_ + c * cc_ + e * sc_);
    double D = (d * c_ - f * s_);
    double E = (2 * (a - c) * sc_ + e * cc_ - e * ss_);
    double F = (d * s_ + f * c_);
    double G = (g * c_ - i * s_);
    double H = (h);
    double I = (g * s_ + i * c_);
    double J = (j);

    a = A;
    b = B;
    c = C;
    d = D;
    e = E;
    f = F;
    g = G;
    h = H;
    i = I;
    j = J;
}
void Quadratic3::rotateZ(double radians) {

    /* x' = xcos(theta) - ysin(theta)
     * y' = xsin(theta) + ycos(theta)
     * z' = z
     *
     * Ax^2 + By^2 + Cz^2 + Dxy + Exz + Fyz + Gx + Hy + Iz + J
     *
     * s = sin(theta)
     * c = cos(theta)
     *
     * Ax'^2 + By'^2 + Cz'^2 + Dx'y' + Ex'z' + Fy'z' + Gx' + Hy' + Iz' + J
     * A(xc - ys)^2 + B(xs + yc)^2 + Cz^2 + D(xc - ys)(xs + yc) + E(xc - ys)z + F(xs + yc)z + G(xc - ys) + H(xs + yc) + Iz + J
     * Accx^2 - 2Acsxy + Assy^2 + Bssx^2 + 2Bscxy + Bccy^2 + Cz^2 + Dcsx^2 + Dccxy - Dssxy - Dscy^2 + Ecxz - Esyz + Fsxz + Fcyz + Gcx - Gsy + Hsx + Hcy + Iz + J
     * (Acc+Dcs+Bss)x^2 + (Ass+Bcc-Dsc)y^2 + (C)z^2 + (2Bsc+Dcc-2Acs-Dss)xy + (Ec+Fs)xz + (Fc-Es)yz + (Gc+Hs)x + (Hc-Gs)y + (I)z + J
     * A' = (Acc+Dcs+Bss)
     * B' = (Ass+Bcc-Dsc)
     * C' = (C)
     * D' = (2Bsc+Dcc-2Acs-Dss)
     * E' = (Ec+Fs)
     * F' = (Fc-Es)
     * G' = (Gc+Hs)
     * H' = (Hc-Gs)
     * I' = (I)
     * J' = (J)
     */

    double s_ = Math::sin(radians);
    double c_ = Math::cos(radians);
    double ss_ = s_ * s_;
    double cc_ = c_ * c_;
    double sc_ = s_ * c_;

    double A = (a * cc_ + d * sc_ + b * ss_);
    double B = (a * ss_ + b * cc_ - d * sc_);
    double C = (c);
    double D = (2 * (b - a) * sc_ + d * cc_ - d * ss_);
    double E = (e * c_ + f * s_);
    double F = (f * c_ - e * s_);
    double G = (g * c_ + h * s_);
    double H = (h * c_ - g * s_);
    double I = (i);
    double J = (j);

    a = A;
    b = B;
    c = C;
    d = D;
    e = E;
    f = F;
    g = G;
    h = H;
    i = I;
    j = J;
}
void Quadratic3::rotate(double r1, double r2, double r3) {

    // Ain't no way I'm hardcoding triple rotation bruh

    rotateX(r1);
    rotateY(r2);
    rotateZ(r3);
}

std::ostream& operator<<(std::ostream& stream, const Quadratic3& rhs) {
    return stream << rhs.a << "x^2 + " << rhs.b << "y^2 + " << rhs.c << "z^2 + " << rhs.d << "xy + " << rhs.e << "xz + " << rhs.f << "yz + " << rhs.g << "x + " << rhs.h << "y + " << rhs.i << "z + " << rhs.j;
}