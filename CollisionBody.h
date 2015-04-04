#ifndef COLLISIONBODY_H_
#define COLLISIONBODY_H_

#include <vector>
#include "Vector.h"

class CCollisionInfo;

class CCollisionBody {
  
public:
    
    std::vector< Vector3< float > > m_ColOffset;
    std::vector< Vector3< float > > m_Axis;
    
    Vector3< float > m_Origin;
    Vector3< float > m_Size;
    
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
    
    const Vector3< float > & GetOrigin() {
     
        return m_Origin;
        
    }
    
    const Vector3< float > & GetSize() {
     
        return m_Size;
        
    }
    
    bool CheckSATCollision( CCollisionInfo &, Vector3< float > &, CCollisionBody *, Vector3< float > & );
    
    
};

class CBoxCollisionBody : public CCollisionBody {
    
public:
    
    CBoxCollisionBody() : CCollisionBody() {
     
        m_Axis.push_back( Vector3< float >( -1.0f, 0.0f, 0.0f ) );
        m_Axis.push_back( Vector3< float >( 0.0f, 1.0f, 0.0f ) );
        
        m_Axis[0].Normalize();
        m_Axis[1].Normalize();
        
    }
    
    void SetBox( float x, float y, float w, float h ) {
     
        m_ColOffset.push_back( Vector3< float >( x, y ) );
        m_ColOffset.push_back( Vector3< float >( x + w, y + h ) );
        
        m_Origin.Set( x, y );
        m_Size.Set( w, h );
        
    }
    
};

class CCollisionInfo {
  
public:
    
    bool collision;
    float minTransDist;
    Vector3< float > minTransAxis;
    
    CCollisionInfo() : collision( false ), minTransDist( 9999.0f ) {
        
    }
    
};

#endif
