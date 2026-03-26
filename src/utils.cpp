#include "utils.h"

float vecDistance(Vector& a, Vector& b)
{
    return (a - b).mag();
}

float vecDistance2(Vector& a, Vector& b)
{
    Vector diff = a - b;
    return diff * diff;
}