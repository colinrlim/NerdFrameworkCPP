#pragma once

struct Quadratic2
{
    double a;
    double b;
    double c;
    double d;
    double e;
    double f;

    Quadratic2(double a, double b, double c, double d, double e, double f);

    double equals(double x, double y);

    void rotate(double radians);
};

