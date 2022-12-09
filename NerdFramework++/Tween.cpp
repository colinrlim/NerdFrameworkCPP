#include "Tween.h"
#include "Math.h"

// https://www.desmos.com/calculator/m8myals511

Tween::Tween() { };

double Tween::linear(double x1, double x2, double interpolant)
{
    if (interpolant < 0) interpolant = 0;
    else if (interpolant > 1) interpolant = 1;

    return x1 + (x2 - x1) * interpolant;
}

double Tween::sineIn(double x1, double x2, double interpolant)
{
    interpolant = Math::sin(Math::PI * interpolant / 2 - Math::PI / 2) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::sineOut(double x1, double x2, double interpolant)
{
    interpolant = Math::sin(Math::PI * interpolant / 2);
    return Tween::linear(x1, x2, interpolant);
}
double Tween::sineInOut(double x1, double x2, double interpolant)
{
    interpolant = Math::sin(Math::PI * interpolant - Math::PI / 2) / 2 + 0.5;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::sineOutIn(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? Math::sin(Math::PI * interpolant) / 2 : Math::sin(Math::PI * interpolant - Math::PI) / 2 + 1;
    return Tween::linear(x1, x2, interpolant);
}

double Tween::backIn(double x1, double x2, double interpolant)
{
    double s = 1.70158;
    interpolant = interpolant * interpolant * (interpolant * (s + 1) - s);
    return Tween::linear(x1, x2, interpolant);
}
double Tween::backOut(double x1, double x2, double interpolant)
{
    double s = 1.70158;
    interpolant = Math::pow(interpolant - 1, 2.0) * ((interpolant - 1) * (s + 1) + s) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::backInOut(double x1, double x2, double interpolant)
{
    double s1 = 2.5949095;
    interpolant = interpolant <= 0.5 ? 2 * interpolant * interpolant * (2 * interpolant * (s1 + 1) - s1) : 0.5 * Math::pow(2 * interpolant - 2, 2.0) * ((2 * interpolant - 2) * (s1 + 1) + s1) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::backOutIn(double x1, double x2, double interpolant)
{
    double s1 = 2.5949095;
    interpolant = 0.5 * Math::pow(2 * interpolant - 1, 2.0) * ((2 * interpolant - 1) * (s1 + 1) + s1 * (interpolant <= 0.5 ? 1 : -1)) + 0.5;
    return Tween::linear(x1, x2, interpolant);
}

double Tween::quadIn(double x1, double x2, double interpolant)
{
    interpolant = Math::pow(interpolant, 2.0);
    return Tween::linear(x1, x2, interpolant);
}
double Tween::quadOut(double x1, double x2, double interpolant)
{
    interpolant = -Math::pow(interpolant - 1, 2.0) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::quadInOut(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? 2 * Math::pow(interpolant, 2.0) : -2 * Math::pow(interpolant - 1, 2.0) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::quadOutIn(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? -2 * Math::pow(interpolant - 0.5, 2.0) + 0.5 : 2 * Math::pow(interpolant - 0.5, 2.0) + 0.5;
    return Tween::linear(x1, x2, interpolant);
}

double Tween::quartIn(double x1, double x2, double interpolant)
{
    interpolant = Math::pow(interpolant, 4.0);
    return Tween::linear(x1, x2, interpolant);
}
double Tween::quartOut(double x1, double x2, double interpolant)
{
    interpolant = -Math::pow(interpolant - 1, 4.0) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::quartInOut(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? 8 * Math::pow(interpolant, 4.0) : -8 * Math::pow(interpolant - 1, 4.0) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::quartOutIn(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? -8 * Math::pow(interpolant - 0.5, 4.0) + 0.5 : 8 * Math::pow(interpolant - 0.5, 4.0) + 0.5;
    return Tween::linear(x1, x2, interpolant);
}

double Tween::quintIn(double x1, double x2, double interpolant)
{
    interpolant = Math::pow(interpolant, 5.0);
    return Tween::linear(x1, x2, interpolant);
}
double Tween::quintOut(double x1, double x2, double interpolant)
{
    interpolant = Math::pow(interpolant - 1, 5.0) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::quintInOut(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? 16 * Math::pow(interpolant, 5.0) : 16 * Math::pow(interpolant - 1, 5.0) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::quintOutIn(double x1, double x2, double interpolant)
{
    interpolant = 16 * Math::pow(interpolant - 0.5, 5.0) + 0.5;
    return Tween::linear(x1, x2, interpolant);
}

double Tween::bounceIn(double x1, double x2, double interpolant)
{
    if (interpolant <= 0.25 / 2.75)
        interpolant = -7.5625 * Math::pow(1.0 - interpolant - 2.625 / 2.75, 2.0) + 0.015625;
    else if (interpolant <= 0.75 / 2.75)
        interpolant = -7.5625 * Math::pow(1.0 - interpolant - 2.25 / 2.75, 2.0) + 0.0625;
    else if (interpolant <= 1.75 / 2.75)
        interpolant = -7.5625 * Math::pow(1.0 - interpolant - 1.5 / 2.75, 2.0) + 0.25;
    else
        interpolant = 1 - 7.5625 * Math::pow(1.0 - interpolant, 2.0);
    return Tween::linear(x1, x2, interpolant);
}
double Tween::bounceOut(double x1, double x2, double interpolant)
{
    if (interpolant <= 1.0 / 2.75)
        interpolant = 7.5625 * interpolant * interpolant;
    else if (interpolant <= 2.0 / 2.75)
        interpolant = 7.5625 * Math::pow(interpolant - 1.5 / 2.75, 2.0) + 0.75;
    else if (interpolant <= 2.5 / 2.75)
        interpolant = 7.5625 * Math::pow(interpolant - 2.25 / 2.75, 2.0) + 0.9375;
    else
        interpolant = 7.5625 * Math::pow(interpolant - 2.625 / 2.75, 2.0) + 0.984375;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::bounceInOut(double x1, double x2, double interpolant)
{
    return Tween::linear(x1, x2, interpolant);
}
double Tween::bounceOutIn(double x1, double x2, double interpolant)
{
    return Tween::linear(x1, x2, interpolant);
}

double Tween::elasticIn(double x1, double x2, double interpolant)
{
    double p = 0.3;
    interpolant = -Math::pow(2.0, 10.0 * (interpolant - 1.0)) * Math::sin(2.0 * Math::PI * (interpolant - 1.0 - p / 4.0) / p);
    return Tween::linear(x1, x2, interpolant);
}
double Tween::elasticOut(double x1, double x2, double interpolant)
{
    double p = 0.3;
    interpolant = Math::pow(2.0, -10.0 * interpolant) * Math::sin(2.0 * Math::PI * (interpolant - p / 4.0) / p) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::elasticInOut(double x1, double x2, double interpolant)
{
    double p1 = 0.45;
    interpolant = interpolant <= 0.5 ? -0.5 * Math::pow(2.0, 20.0 * interpolant - 10.0) * Math::sin(2.0 * Math::PI * (2.0 * interpolant - 1.1125) / p1) : 0.5 * Math::pow(2.0, -20.0 * interpolant + 10.0) * Math::sin(2.0 * Math::PI * (2.0 * interpolant - 1.1125) / p1) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::elasticOutIn(double x1, double x2, double interpolant)
{
    double p1 = 0.45;
    interpolant = interpolant <= 0.5 ? 0.5 * Math::pow(2.0, -20.0 * interpolant) * Math::sin(2.0 * Math::PI * (2.0 * interpolant - p1 / 4.0) / p1) + 0.5 : -0.5 * Math::pow(2.0, 10.0 * (2.0 * interpolant - 2.0)) * Math::sin(2.0 * Math::PI * (2.0 * interpolant - 2.0 - p1 / 4.0) / p1) + 0.5;
    return Tween::linear(x1, x2, interpolant);
}

double Tween::exponentialIn(double x1, double x2, double interpolant)
{
    interpolant = Math::pow(2.0, 10.0 * interpolant - 10.0) - 0.001;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::exponentialOut(double x1, double x2, double interpolant)
{
    interpolant = -1.001 * Math::pow(2.0, -10.0 * interpolant) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::exponentialInOut(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? 0.5 * Math::pow(2.0, 20.0 * interpolant - 10.0) - 0.0005 : 0.50025 * -Math::pow(2.0, -20.0 * interpolant + 10.0) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::exponentialOutIn(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? 0.5005 * -Math::pow(2.0, -20.0 * interpolant) + 0.5005 : 0.5 * Math::pow(2.0, 10.0 * (2.0 * interpolant - 2.0)) + 0.4995;
    return Tween::linear(x1, x2, interpolant);
}

double Tween::circularIn(double x1, double x2, double interpolant)
{
    interpolant = -Math::pow(1.0 - Math::pow(interpolant, 2.0), 0.5) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::circularOut(double x1, double x2, double interpolant)
{
    interpolant = Math::pow(-Math::pow(interpolant - 1.0, 2.0) + 1.0, 0.5);
    return Tween::linear(x1, x2, interpolant);
}
double Tween::circularInOut(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? -Math::pow(-Math::pow(interpolant, 2.0) + 0.25, 0.5) + 0.5 : Math::pow(-Math::pow(interpolant - 1.0, 2.0) + 0.25, 0.5) + 0.5;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::circularOutIn(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? Math::pow(-Math::pow(interpolant - 0.5, 2.0) + 0.25, 0.5) : -Math::pow(-Math::pow(interpolant - 0.5, 2.0) + 0.25, 0.5) + 1;
    return Tween::linear(x1, x2, interpolant);
}

double Tween::cubicIn(double x1, double x2, double interpolant)
{
    interpolant = Math::pow(interpolant, 3.0);
    return Tween::linear(x1, x2, interpolant);
}
double Tween::cubicOut(double x1, double x2, double interpolant)
{
    interpolant = Math::pow(interpolant - 1, 3.0) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::cubicInOut(double x1, double x2, double interpolant)
{
    interpolant = interpolant <= 0.5 ? 4 * Math::pow(interpolant, 3.0) : 4 * Math::pow(interpolant - 1, 3.0) + 1;
    return Tween::linear(x1, x2, interpolant);
}
double Tween::cubicOutIn(double x1, double x2, double interpolant)
{
    interpolant = 4 * Math::pow(interpolant - 0.5, 3.0) + 0.5;
    return Tween::linear(x1, x2, interpolant);
}