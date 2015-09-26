#ifndef COLLISIONENGINE_H_
#define COLLISIONENGINE_H_

#include "SpatialTree.h"
#include "WorldEntity.h"
#include "CollisionBody.h"

class CCollisionContact {
  
private:
    
    void * m_pObjectA, * m_pObjectB;
    CCollisionInfo * m_pCollisionInfo;
    
public:
    
    void SetObjects( void * pObjA, void * pObjB ) {
     
        m_pObjectA = pObjA;
        m_pObjectB = pObjB;
        
    }
    
    void SetCollisionInfo( CCollisionInfo * pCollisionInfo ) {
     
        m_pCollisionInfo = pCollisionInfo;
        
    }
    
    CCollisionInfo * GetCollisionInfo() {
     
        return m_pCollisionInfo;
        
    }
    
    void * GetObjectA() {
     
        return m_pObjectA;
        
    }
    
    void * GetObjectB() {
     
        return m_pObjectB;
        
    }
    
};

class CCollisionListener {

protected:

public:

    virtual void BeginContact( CCollisionContact & c ) = 0;
    
    
};

class CCollisionEngine {
  
private:
    
public:
    
    void CheckForQuadTreeCollisions( CSpatialTree *, CCollisionListener * );
    
};

#endif
