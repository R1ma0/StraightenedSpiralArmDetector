#include "gauss_block_size_checker.hpp"

int CheckGBSValue(int value, int* gbsOldValue)
{
    int newValue = value;

    if (value % 2 == 0)
    {
        if (value - *gbsOldValue > 0) { newValue = value + 1; }
        if (value - *gbsOldValue < 0) { newValue = value - 1; }
    }

    *gbsOldValue = newValue;

    return newValue;
}
