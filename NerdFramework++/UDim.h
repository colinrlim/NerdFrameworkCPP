#pragma once

struct UDim
{
    double scale;
    double offset;

    UDim();
    UDim(double scale, double offset);

    double absolute(double max) const;
};

