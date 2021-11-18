#pragma once
#include "Windows.h"

namespace
{
    POINT operator+(POINT one, POINT second)
    {
        POINT result = { one.x + second.x, one.y + second.y };
        return result;
    }

    bool operator==(POINT one, POINT second)
    {
        return (one.x == second.x && one.y == second.y);
    }

    bool operator!=(POINT one, POINT second)
    {
        return (one.x != second.x || one.y != second.y);
    }
}
