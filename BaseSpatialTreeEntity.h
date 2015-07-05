#ifndef SPATIAL_TREE_ENTITY_H_
#define SPATIAL_TREE_ENTITY_H_

#include "Vector.h"

class CBaseSpatialTreeEntity {
    
protected:
    
    
    Vector3< float > m_Pos, m_Size;
    int m_EntityID;
    bool m_bShouldKill;
    bool m_bShouldUpdate;
    
    
public:
    
    CBaseSpatialTreeEntity() : m_EntityID( -1 ), m_bShouldKill( false ), m_bShouldUpdate( false ) {
        
    }
    
    void SetEntityID( int id ) {
        
        m_EntityID = id;
        
    }
    
    int GetEntityID() {
        
        return m_EntityID;
        
    }
    
    void SetPos( float x, float y ) {
        
        m_Pos.Set( x, y );
        
    }

	void SetPos( float x, float y, float z ) {
	
		m_Pos.Set( x, y, z );
	
	}
    
    void SetSize( float x, float y ) {
        
        m_Size.Set( x, y );
        
    }

	void GetPos( float * x, float * y, float * z ) {
	
		*x = m_Pos.GetX();
		*y = m_Pos.GetY();
		*z = m_Pos.GetZ();

	}
    
    void GetPos( float * x, float * y ) {
        
        *x = m_Pos.GetX();
        *y = m_Pos.GetY();
        
    }

	void GetSize( float * x, float * y, float * z ) {
	
		*x = m_Size.GetX();
		*y = m_Size.GetY();
		*z = m_Size.GetZ();
	
	}
    
    void GetSize( float * x, float * y ) {
        
        *x = m_Size.GetX();
        *y = m_Size.GetY();
        
    }
    
    void SetShouldKill( bool b ) {
    
        m_bShouldKill = b;
        
    }
    
    bool GetShouldKill() {
     
        return m_bShouldKill;
        
    }
    
    void SetShouldUpdate( bool b ) {
     
        m_bShouldUpdate = b;
        
    }
    
    bool GetShouldUpdate() {
     
        return m_bShouldUpdate;
        
    }
    
};

#endif
