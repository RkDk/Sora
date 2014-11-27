#ifndef UTIL_H_
#define UTIL_H_

#include "Vector.h"

#include <cmath>
#include <cstdlib>

namespace Util
{
    
    void FixAppleRelativeDirectory();
    
    float Dist( float, float, float, float );
    float Dist( Vector2< float >, Vector2< float > );
    float MaxF( float, float, float );
    float MinF( float, float, float );
    float MinMaxF( float, float, float );
    
    int RandomNumber( int, int );

}

#endif
