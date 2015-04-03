#ifndef COLLISIONBODY_H_
#define COLLISIONBODY_H_

#include <vector>
#include "Vector.h"

class CCollisionInfo;

class CCollisionBody {
  
private:
    
    std::vector< Vector3< float > > m_ColOffset;
    std::vector< Vector3< float > > m_Axis;
    
    void FindSATMinMax( const std::vector< Vector3< float > > &, Vector3< float > &, Vector3< float > &, float *, float * );
    
public:
    
    const Vector3< float > & GetAxis( unsigned long int i ) {
     
        return m_Axis[i];
        
    }
    
    const std::vector< Vector3< float > > & GetOffsets() {
     
        return m_ColOffset;
        
    }

    const Vector3< float > & GetOffset( unsigned long int i ) {
        
        return m_ColOffset[i];
        
    }

    
    unsigned long int GetAxisCount() {
    
        return m_Axis.size();
        
    }
    
    
    
    bool CheckSATCollision( CCollisionInfo &, Vector3< float > &, CCollisionBody *, Vector3< float > & );
    
    
};

class CCollisionInfo {
  
public:
    
    float minTransDist;
    Vector3< float > minTransAxis;
    
    CCollisionInfo() : minTransDist( 9999.0f ) {
        
    }
    
};

#endif
