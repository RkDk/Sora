#ifndef COLLISIONINFO_H_
#define COLLISIONINFO_H_


class CCollisionInfo {
    
public:
    
    bool collision;
    float minTransDist;
    Vector3< float > minTransAxis;
    
    CCollisionInfo() : collision( false ), minTransDist( 9999.0f ) {
        
    }
    
};


#endif
