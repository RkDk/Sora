#include "Util.h"


#ifdef __APPLE__
    #include "CoreFoundation/CoreFoundation.h"
#endif

int Util::RandomNumber( int min, int max )
{

	return ( int )( rand() % ( max + 1 - min ) ) + min;

}

float Util::MinF( float val, float n, float min ) {
 
    val += n;
    
    if( val < min )
        return min;
    
    return val;
    
}

float Util::MaxF( float val, float n, float max ) {
 
    val += n;
    
    if( val > max )
        return max;
    
    return val;
    
}

float Util::MinMaxF( float val, float n, float minmax ) {
 
    if( val > minmax )
        return Util::MinF( val, n, minmax );
    
    return Util::MaxF( val, n, minmax );
    
}

float Util::Dist( float x1, float y1, float x2, float y2 ) {
 
    float xdist = x1 - x2;
    float ydist = y1 - y2;
    
    return sqrtf( xdist*xdist + ydist*ydist );
    
}

float Util::Dist( Vector2< float > p1, Vector2< float > p2 ) {
 
    return Util::Dist( p1.GetX(), p1.GetY(), p2.GetX(), p2.GetY() );
    
}


float Util::AngleBetweenPoints( float x1, float y1, float x2,  float y2 ) {
 

    return ( std::atan2( y2 - y1, x2 - x1 ) ) * RAD2DEG;
    
}

void Util::FixAppleRelativeDirectory() {


    #ifdef __APPLE__
        CFBundleRef mainBundle = CFBundleGetMainBundle();
        CFURLRef resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
        char path[PATH_MAX];
    
        if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, PATH_MAX))
        {
            return;
        }
    
        CFRelease(resourcesURL);
        
        chdir(path);
    #endif
    
}