#ifndef SPATIALTREE_H_
#define SPATIALTREE_H_

#include <utility>
#include <unordered_map>

#include "Vector.h"
#include "BaseSpatialTreeEntity.h"
#include "WorldEntity.h"
#include "DrawContext.h"

#define MINIMUM_QT_SIZE 200

class CSpatialTreeObject : public CBaseSpatialTreeEntity {
    
private:
    
    CWorldEntity * m_pObject;


public:
    
    CWorldEntity * GetEntity() {
     
        return m_pObject;
        
    }

    CSpatialTreeObject() : CBaseSpatialTreeEntity(), m_pObject( 0 ) {
        
    }
    
    CSpatialTreeObject( CWorldEntity * obj ) : CBaseSpatialTreeEntity(), m_pObject( obj ) {
        
    }
    
    
};

class CNodeList {
  
public:
    
    int m_NodeID;
    std::vector< CSpatialTreeObject * > m_pNodeObjects;
    
    CNodeList( int id ) : m_NodeID( id ) {
        
    }
    
    CNodeList() : m_NodeID( -1 ) {
        
    }
    
};


class CSpatialTree {
  
protected:
    
    CSpatialTree * m_pChildNodes, * m_pParentNode;
    int m_CurLayer, m_NumNodes;
    Vector3< int > m_Pos, m_Size;
    
    std::unordered_map< int, CSpatialTreeObject * > m_pQTObjects;
    void RemoveObject( CSpatialTreeObject *, bool );
    void InsertObject( CSpatialTreeObject * );
    void RemoveIfObjectHasMoved( CSpatialTreeObject * );
    
    bool IsEmpty() {
     
        return m_pQTObjects.size() == 0;
        
    }
    
    bool ContainsEntityCount( int n ) {
     
        return ( m_pQTObjects.size() >= n );
        
    }
    
    bool ContainsSpace3D( float x, float y, float z, float w, float h, float d ) {
     
        if( ContainsSpace2D( x, y, w, h ) ) 
			if( z <= m_Pos.GetZ() && z >= m_Pos.GetZ() + d )
				return true;
        
        return false;
        
    }

    bool ContainsSpace2D( float x, float y, float w, float h ) {
     
        float w2 = m_Size.GetX();
        float h2 = m_Size.GetY();
        
        if( !Util::ContainsPoint( x, y, m_Pos.GetX() - w, m_Pos.GetY() - h, m_Size.GetX() + w, m_Size.GetY() + h ) )
            if( !Util::ContainsPoint( m_Pos.GetX(), m_Pos.GetY(), x - w2, y - h2, w + w2, h + h2 ) )
                return false;
        
        return true;
        
    }

	virtual bool ContainsObject( CSpatialTreeObject * o ) = 0;
    
public:
    
    CSpatialTree() : m_pChildNodes( NULL ), m_pParentNode( NULL ), m_CurLayer( 1 ) {
        
    }
    
    virtual void Draw( CDrawContext * ) = 0;

    void Think();
    void GetObjectsInLayer( std::vector< CNodeList > &, int  );
    
    CSpatialTreeObject * AddEntity( CWorldEntity * );
    
    bool HasEntity( CSpatialTreeObject * );
    
    int GetNumberOfNodesInLayer( int l ) {
     
        return pow( m_NumNodes, l );
        
    }
    
    virtual ~CSpatialTree();
    
    
};

class CSpatialOctree : public CSpatialTree {

protected:

	void CreateTree( int, int, int, int, int );

	bool ContainsObject( CSpatialTreeObject * o ) {
	
		int x, y, z;
		int w, h, d;

		o->GetPos( &x, &y, &z );
		o->GetSize( &w, &h, &d );

		return ContainsSpace3D( x, y, z, w, h, d );
	
	}
};

class CSpatialQuadTree : public CSpatialTree {

protected:

	virtual void CreateTree( int, int, int, int );
	void Draw( CDrawContext * );

	bool ContainsObject( CSpatialTreeObject * o ) {
	
		int x, y;
		int w, h;

		o->GetPos( &x, &y );
		o->GetSize( &w, &h );

		return ContainsSpace2D( x, y, w, h );
	
	}

};

#endif