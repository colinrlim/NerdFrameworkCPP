#pragma once

#include "Vector2.h"
#include "UDim.h"

struct UDim2
{
    UDim x;
    UDim y;

    UDim2();
    UDim2(double xScale, double xOffset, double yScale, double yOffset);
    UDim2(double xOffset, double yOffset);
    UDim2(const UDim& x, const UDim& y);

    static const UDim2 zero;
    static const UDim2 one;

    static UDim2 fromScale(double xScale, double yScale);
    static UDim2 fromOffset(double xOffset, double yOffset);

    Vector2 absolute(double width, double height) const;
};

std::ostream& operator<<(std::ostream& stream, const UDim2& rhs);

