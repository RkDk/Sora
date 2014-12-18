#ifndef UTIL_H_
#define UTIL_H_

#include "Vector.h"

#include <cmath>
#include <cstdlib>


#define DEG2RAD 0.017453f
#define RAD2DEG 57.29577f

namespace Util
{
    
    void FixAppleRelativeDirectory();
    
    float Dist( float, float, float, float );
    float Dist( Vector2< float >, Vector2< float > );
    float MaxF( float, float, float );
    float MinF( float, float, float );
    float MinMaxF( float, float, float );
    float AngleBetweenPoints( float, float, float, float );
    
    int RandomNumber( int, int );

}

#endif
