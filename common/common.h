#pragma once

#include <cmath>
#include <ctime>

const double EPS = 1e-12;

void init_random_sequence()
{
    srand(time(nullptr));
}

void init_random_sequence(unsigned int seed)
{
    srand(seed);
}

double nextRandom()
{
    return (double)rand() / RAND_MAX;
}

