#pragma once

namespace MathTools
{
    template<class T> T Min(T a, T b)
    {
        return a < b ? a : b;
    }

    template<class T> T Max(T a, T b)
    {
        return a > b ? a : b;
    }
}
