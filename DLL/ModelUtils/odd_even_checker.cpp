#include "pch.h"
#include "odd_even_checker.hpp"

int CheckOddValue(int value, int* oldValue)
{
    int newValue = value;

    if (value % 2 == 0)
    {
        if (value - *oldValue > 0) { newValue = value + 1; }
        if (value - *oldValue < 0) { newValue = value - 1; }
    }

    *oldValue = newValue;

    return newValue;
}

int CheckEvenValue(int value, int* oldValue)
{
    int newValue = value;

    if (value % 2 == 1)
    {
        if (value - *oldValue > 0) { newValue = value + 1; }
        if (value - *oldValue < 0) { newValue = value - 1; }
    }

    *oldValue = newValue;

    return newValue;
}