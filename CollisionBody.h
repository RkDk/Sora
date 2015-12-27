#ifndef COLLISIONBODY_H_
#define COLLISIONBODY_H_

#include <vector>
#include "Vector.h"
#include "CollisionInfo.h"
#include "Util.h"
#include "Logging.h"

class CCollisionBody {
  
public:
    
    std::vector< Vector3< float > > m_ColOffset;
    std::vector< Vector3< float > > m_Axis;
    std::vector< Vector3< float > > m_Normal;
    
    Vector3< float > m_Origin;
    Vector3< float > m_Size;
    Vector3< float > m_Displacement;
    
    void FindSATMinMax( const std::vector< Vector3< float > > &, Vector3< float > &, Vector3< float > &, float *, float * );
    
public:
    
    void ClearNormals() {
        
        m_Normal.clear();
        
    }
    
    bool HasNormal( float x, float y, float z ) {
        
        for( auto iter : m_Normal ) {
            if( iter.GetX() == x )
                if( iter.GetY() == y )
                    if( iter.GetZ() == z )
                        return true;
        }
        
        return false;
        
    }
    
    void AddNormal( float x, float y, float z ) {
        m_Normal.push_back( Vector3< float >( x, y, z ) );
    }
    
    virtual void SetDefaultNormals() { }
    
    
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
    
    const Vector3< float > & GetDisplacement() {
        
        return m_Displacement;
        
    }
    
    void SetDisplacement( Vector3< float > & disp ) {
        
        m_Displacement = disp;
        
    }
    
    bool CheckSATCollision( CCollisionInfo &, Vector3< float > &, CCollisionBody *, Vector3< float > & );
    
    
};

class CBoxCollisionBody : public CCollisionBody {
    
public:
    
    CBoxCollisionBody() : CCollisionBody() {
        
        m_Axis.clear();
     
        m_Axis.push_back( Vector3< float >( -1.0f, 0.0f, 0.0f ) );
        m_Axis.push_back( Vector3< float >( 0.0f, 1.0f, 0.0f ) );
        
        m_Axis[0].Normalize();
        m_Axis[1].Normalize();
        
        SetDefaultNormals();
        
    }
    
    void SetDefaultNormals() {
        
        m_Normal.push_back( Vector3< float >( -1.0f, 0.0f, 0.0f ) );
        m_Normal.push_back( Vector3< float >( 1.0f, 0.0f, 0.0f ) );
        m_Normal.push_back( Vector3< float >( 0.0f, -1.0f, 0.0f ) );
        m_Normal.push_back( Vector3< float >( 0.0f, 1.0f, 0.0f ) );
        
    }
    
    void FitFromCenter( float w1, float h1, float w2, float h2 ) {
     
        float x = w1 * .5f - w2 * .5f;
        float y = h1 * .5f - h2 * .5f;
        
        SetBox( x, y, w2, h2 );
        
    }
    
    void SetBox( float x, float y, float w, float h ) {
        
        m_ColOffset.clear();
     
        m_ColOffset.push_back( Vector3< float >( x, y ) );
        m_ColOffset.push_back( Vector3< float >( x + w, y + h ) );
        
        m_Origin.Set( x, y );
        m_Size.Set( w, h );
        
    }
    
};

#endif
