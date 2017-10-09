#include "myMath.h"

#include <cstdlib>

int MyMath::RandomNumber( const int& min, const int& max )
{
    int range = max - min;
    return (rand() % range) + min;
}
