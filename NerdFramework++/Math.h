#pragma once

#include <functional>
#include <vector>
#include <limits>

#define PI         3.1415926535897931
#define HALF_PI    1.57079632679
#define QUARTER_PI 0.78539816339
#define TWO_PI     6.28318530718

class Math
{
private:
    Math() = delete;
public:
    static double dmod(double x, double mod);

    static double degreesToRadians(double degrees);
    static double radiansToDegrees(double radians);

    static double fromParameterization3(double t, double s, double a, double b, double c);

    static double average(std::vector<double> values);

    static double min(double a, double b);
    static double min(std::vector<double> values);
    static double max(double a, double b);
    static double max(std::vector<double> values);
    static std::initializer_list<double> bounds(std::vector<double> values);
    static std::initializer_list<size_t> boundsIndex(std::vector<double> values);
    static size_t minIndex(std::vector<double> values);
    static size_t maxIndex(std::vector<double> values);

    static double constrain(double x, double min, double max);
    static double abs(double x);
    static int floor(double x);
    static int ceil(double x);

    static double sqrt(double x, int steps = 20);
    static double pow(double x, int n);
    static double pow(double x, double n);
    static int ipow(int x, int n);

    static int factorial(int x);

    static double integrate(std::function<double(double)> function, double a, double b, int steps = 1000);

    static double sin(double radians, int steps = 10);
    static double asin(double d, int steps = 10);
    static double cos(double radians, int steps = 10);
    static double acos(double d, int steps = 10);
    static double tan(double radians, int steps = 10);
    static double atan(double d, int steps = 10);
    static double cot(double radians);
    static double acot(double d);
    
    static double log(double x, double y);
};

