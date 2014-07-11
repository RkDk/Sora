#include "Util.h"

int Util::RandomNumber( int min, int max )
{

    return ( ( int )rand() % ( max - min ) + 1 ) + min;

}
