#pragma once

class Tween
{
private:
    Tween() = delete;
public:
    static double linear(double x1, double x2, double interpolant);

    static double sineIn(double x1, double x2, double interpolant);
    static double sineOut(double x1, double x2, double interpolant);
    static double sineInOut(double x1, double x2, double interpolant);
    static double sineOutIn(double x1, double x2, double interpolant);

    static double backIn(double x1, double x2, double interpolant);
    static double backOut(double x1, double x2, double interpolant);
    static double backInOut(double x1, double x2, double interpolant);
    static double backOutIn(double x1, double x2, double interpolant);

    static double quadIn(double x1, double x2, double interpolant);
    static double quadOut(double x1, double x2, double interpolant);
    static double quadInOut(double x1, double x2, double interpolant);
    static double quadOutIn(double x1, double x2, double interpolant);

    static double quartIn(double x1, double x2, double interpolant);
    static double quartOut(double x1, double x2, double interpolant);
    static double quartInOut(double x1, double x2, double interpolant);
    static double quartOutIn(double x1, double x2, double interpolant);

    static double quintIn(double x1, double x2, double interpolant);
    static double quintOut(double x1, double x2, double interpolant);
    static double quintInOut(double x1, double x2, double interpolant);
    static double quintOutIn(double x1, double x2, double interpolant);

    static double bounceIn(double x1, double x2, double interpolant);
    static double bounceOut(double x1, double x2, double interpolant);
    static double bounceInOut(double x1, double x2, double interpolant);
    static double bounceOutIn(double x1, double x2, double interpolant);

    static double elasticIn(double x1, double x2, double interpolant);
    static double elasticOut(double x1, double x2, double interpolant);
    static double elasticInOut(double x1, double x2, double interpolant);
    static double elasticOutIn(double x1, double x2, double interpolant);

    static double exponentialIn(double x1, double x2, double interpolant);
    static double exponentialOut(double x1, double x2, double interpolant);
    static double exponentialInOut(double x1, double x2, double interpolant);
    static double exponentialOutIn(double x1, double x2, double interpolant);

    static double circularIn(double x1, double x2, double interpolant);
    static double circularOut(double x1, double x2, double interpolant);
    static double circularInOut(double x1, double x2, double interpolant);
    static double circularOutIn(double x1, double x2, double interpolant);

    static double cubicIn(double x1, double x2, double interpolant);
    static double cubicOut(double x1, double x2, double interpolant);
    static double cubicInOut(double x1, double x2, double interpolant);
    static double cubicOutIn(double x1, double x2, double interpolant);
};

