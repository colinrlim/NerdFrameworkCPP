#pragma once

#include <ostream>

struct UDim
{
    double scale;
    double offset;

    UDim();
    UDim(double scale, double offset);

    double absolute(double max) const;
};

std::ostream& operator<<(std::ostream& stream, const UDim& rhs);

