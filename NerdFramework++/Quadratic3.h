#pragma once

#include <ostream>

struct Quadratic3
{
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;
    double g;
    double h;
    double i;
    double j;

    Quadratic3(double a, double b, double c, double d, double e, double f, double g, double h, double i, double j);

    double equals(double x, double y, double z);

    void rotateX(double radians);
    void rotateY(double radians);
    void rotateZ(double radians);
    void rotate(double r1, double r2, double r3);
};

std::ostream& operator<<(std::ostream& stream, const Quadratic3& rhs);

