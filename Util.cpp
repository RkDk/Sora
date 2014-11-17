#include "Util.h"


#ifdef __APPLE__
    #include "CoreFoundation/CoreFoundation.h"
#endif

int Util::RandomNumber( int min, int max )
{

	return ( int )( rand() % ( max + 1 - min ) ) + min;

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