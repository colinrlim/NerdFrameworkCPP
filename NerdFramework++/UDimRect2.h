#pragma once
#include "Vector2.h"
#include "UDim2.h"

struct UDimRect2
{
    UDim2 p;
    UDim2 s;

    UDimRect2(const UDim2& position, const UDim2& size);
    UDimRect2(const Vector2& position, const Vector2& size);

    static const UDimRect2 one;

    bool overlaps(const Vector2& point, int windowWidth = 0, int windowHeight = 0) const;
    bool overlaps(const UDimRect2& rectangle, int windowWidth = 0, int windowHeight = 0) const;
};

std::ostream& operator<<(std::ostream& stream, const UDimRect2& rhs);

