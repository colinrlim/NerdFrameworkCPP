#pragma once
#include <SDL.h>
#include "Vector2.h"
#include "Image4.h"

struct Triangle2
{
public:
    Vector2& a;
    Vector2& b;
    Vector2& c;

    Triangle2(Vector2& a, Vector2& b, Vector2& c);

    double area();

    static Vector2 parameterization(const Vector2& a, const Vector2& b, const Vector2& c, const Vector2& point);
    Vector2 parameterization(const Vector2& point);

    bool meets(const Vector2& point);
};

