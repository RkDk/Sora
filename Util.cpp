#include "Util.h"

int Util::RandomNumber( int min, int max )
{

	return ( int )( rand() % ( max + 1 - min ) ) + min;

}
