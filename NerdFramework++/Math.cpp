#include <vector>
#include <cmath>
#include "Tween.h"
#include "Math.h"

double Math::dmod(double x, double mod)
{
    return !mod ? x : x - mod * static_cast<long long>(x / mod);
}

double Math::degreesToRadians(double degrees)
{
    /* Radians => Complete Rotation: 2*PI
     * Degrees => Complete Rotation: 360
     *
     * Conversion:
     * Degrees => Radians
     * (x / 360) * (2 * PI)
     * (x * PI) / 180
     */

    return (degrees * PI) / 180.0;
}
double Math::radiansToDegrees(double radians)
{
    /* Radians => Complete Rotation: 2*PI
     * Degrees => Complete Rotation: 360
     *
     * Conversion:
     * Degrees => Radians
     * (x / [2 * PI]) * 360.0
     * (x * 180) / PI
     */

    return (radians * 180.0) / PI;
}

double Math::fromParameterization3(double t, double s, double a, double b, double c)
{
    return a * (1.0 - t - s) + b * t + c * s;
}
double Math::random(double min, double max) {
    return Math::random((int)(min * 1000.0), (int)(max * 1000.0)) / 1000.0;
}
int Math::random(int min, int max) {
    if (min == max)
        return min;
    return rand() % (min - max) + min;
}

double Math::average(std::vector<double> values)
{
    double total = 0.0;
    for (size_t i = 0; i < values.size(); i++)
    {
        total += values[i];
    }
    return total / values.size();
}

double Math::min(double a, double b)
{
    if (a <= b) return a;
    return b;
}

double Math::min(std::vector<double> values)
{
    double min = values[0];
    for (size_t i = 1; i < values.size(); i++)
    {
        if (values[i] < min)
            min = values[i];
    }
    return min;
}

double Math::max(double a, double b)
{
    if (a >= b) return a;
    return b;
}

double Math::max(std::vector<double> values)
{
    double max = values[0];
    for (size_t i = 1; i < values.size(); i++)
    {
        if (values[i] > max)
            max = values[i];
    }
    return max;
}

std::initializer_list<double> Math::bounds(std::vector<double> values)
{
    double min = values[0];
    double max = values[0];
    for (size_t i = 1; i < values.size(); i++)
    {
        if (values[i] > max)
            max = values[i];
        else if (values[i] < min)
            min = values[i];
    }
    return { min, max };
}

std::initializer_list<size_t> Math::boundsIndex(std::vector<double> values)
{
    size_t min = 0;
    size_t max = 0;
    for (size_t i = 1; i < values.size(); i++)
    {
        if (values[i] > values[max])
            max = i;
        else if (values[i] < values[min])
            min = i;
    }
    return { min, max };
}

size_t Math::minIndex(std::vector<double> values)
{
    double min = values[0];
    size_t index = 0;
    for (size_t i = 1; i < values.size(); i++)
    {
        if (values[i] < min)
        {
            min = values[i];
            index = i;
        }
    }
    return index;
}

size_t Math::maxIndex(std::vector<double> values)
{
    double min = values[0];
    size_t index = 0;
    for (size_t i = 1; i < values.size(); i++)
    {
        if (values[i] > min)
        {
            min = values[i];
            index = i;
        }
    }
    return index;
}

double Math::constrain(double x, double min, double max)
{
    if (x > max)
        return max;
    if (x < min)
        return min;
    return x;
}

double Math::abs(double x)
{
    return x < 0.0 ? -x : x;
}

int Math::floor(double x)
{
    return (int)std::floor(x);
}

int Math::ceil(double x)
{
    return (int)std::ceil(x);
}

double Math::sqrt(double x, int steps)
{
    return std::sqrt(x);
    /* fast inverse square root (quake) algorithm
    */

    /*uint32_t i = *reinterpret_cast<uint32_t*>(&x);

    i = 0x5f375a86 - (i >> 1);
    double result = *reinterpret_cast<double*>(&i);
    result *= 1.5 - 0.5 * x * result * result;

    return result * (1.5 - 0.5 * x * result * result);*/
}

double Math::pow(double x, int n)
{
    double x1 = 1.0;
    if (n == 0) return x1;

    for (int i = 0; i < Math::abs(n); i++)
    {
        x1 *= x;
    }

    if (n < 0) return 1 / x1;
    return x1;
}

double Math::pow(double x, double n)
{
    return std::pow(x, n);
    //return pow(x, (int)(n*10)) / pow(x, 10);
}

int Math::ipow(int x, int n) {
    int result = 1;
    for (size_t i = 1; i <= n; i++)
        result *= x;
    return result;
}

int Math::factorial(int x)
{
    int x1 = 1;
    for (int i = 1; i <= x; i++)
    {
        x1 *= i;
    }

    return x1;
}

double Math::integrate(std::function<double(double)> function, double a, double b, int steps)
{
    double x1 = 0.0;
    for (int i = 0; i < steps; i++)
    {
        x1 += function(Tween::linear(a, b, (double)i / steps)) / steps;
    }

    return x1;
}

double Math::sin(double radians, int steps)
{
    return std::sin(radians);

    /* Possible fast solution?
     * https://gamedev.stackexchange.com/a/4780
     */

     /*
     double x1 = 0.0;

     for (size_t i = 1; i <= steps; i++)
     {
         x1 += pow(radians, i * 2) / Factorial(i * 2) * (i % 2 == 0 ? -1 : 1);
     }

     return x1;*/
}

double Math::asin(double d, int steps)
{
    return std::asin(d);
    /*if (d < -1 || d > 1) return 0.0;
    double x1 = 0.0;

    for (size_t i = 0; i < steps; i++)
    {
        x1 += (Factorial(i * 2) / (pow(2, i * 2) * pow(Factorial(i), 2))) * (pow(d, (2*i) + 1)/((2*i) + 1));
    }

    return x1*/
}

double Math::cos(double radians, int steps)
{
    return std::cos(radians);
    /*double x1 = 0.0;

    for (size_t i = 0; i < steps; i++)
    {
        x1 += pow(radians, i * 2) / Factorial(i * 2) * (i % 2 == 1 ? -1 : 1);
    }

    return x1;*/
}

double Math::acos(double d, int steps)
{
    return std::acos(d);
    /*if (d < -1 || d > 1) return 0.0;
    return PI / 2.0 - Asin(d, steps);*/
}

double Math::tan(double radians, int steps)
{
    return std::tan(radians);
}

double Math::atan(double d, int steps)
{
    return std::atan(d);
}

double Math::cot(double radians)
{
    return 1.0 / std::tan(radians);
}

double Math::acot(double d)
{
    return std::atan(1.0 / d);
}

double Math::log(double x, double y)
{
    return 1.0;
}