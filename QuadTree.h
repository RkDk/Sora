#ifndef QUADTREE_H_
#define QUADTREE_H_

#include <utility>
#include <unordered_map>

#include "Vector.h"
#include "WorldEntity.h"
#include "DrawContext.h"

#define MINIMUM_QT_SIZE 200

class CQuadTreeObject : public CBaseQuadTreeEntity {
    
private:
    
    CWorldEntity * m_pObject;


public:
    
    CWorldEntity * GetEntity() {
     
        return m_pObject;
        
    }

    CQuadTreeObject() : CBaseQuadTreeEntity(), m_pObject( 0 ) {
        
    }
    
    CQuadTreeObject( CWorldEntity * obj ) : CBaseQuadTreeEntity(), m_pObject( obj ) {
        
    }
    
    
};

class CNodeList {
  
public:
    
    int m_NodeID;
    std::vector< CQuadTreeObject * > m_pNodeObjects;
    
    CNodeList( int id ) : m_NodeID( id ) {
        
    }
    
    CNodeList() : m_NodeID( -1 ) {
        
    }
    
};


class CQuadTree {
  
private:
    
    CQuadTree * m_pChildNodes, * m_pParentNode;
    int m_CurLayer;
    Vector2< int > m_Pos, m_Size;
    
    
    std::unordered_map< int, CQuadTreeObject * > m_pQTObjects;
    void RemoveObject( CQuadTreeObject *, bool );
    void InsertObject( CQuadTreeObject * );
    void RemoveIfObjectHasMoved( CQuadTreeObject * );
    
    bool IsEmpty() {
     
        return m_pQTObjects.size() == 0;
        
    }
    
    bool ContainsEntityCount( int n ) {
     
        return ( m_pQTObjects.size() >= n );
        
    }
    
    bool ContainsSpace( float x, float y, float w, float h ) {
     
        float w2 = m_Size.GetX();
        float h2 = m_Size.GetY();
        
        if( !Util::ContainsPoint( x, y, m_Pos.GetX() - w, m_Pos.GetY() - h, m_Size.GetX() + w, m_Size.GetY() + h ) )
            if( !Util::ContainsPoint( m_Pos.GetX(), m_Pos.GetY(), x - w2, y - h2, w + w2, h + h2 ) )
                return false;
        
        return true;
        
    }
    
public:
    
    CQuadTree() : m_pChildNodes( NULL ), m_pParentNode( NULL ), m_CurLayer( 1 ) {
        
    }
    
    void Draw( CDrawContext * );
    
    void Init( int, int, int, int );
    void Init( int, int, int );
    
    void Think();
    void GetObjectsInLayer( std::vector< CNodeList > &, int  );
    
    CQuadTreeObject * AddEntity( CWorldEntity * );
    
    bool HasEntity( CQuadTreeObject * );
    
    int GetNumberOfNodesInLayer( int l ) {
     
        return pow( 4, l );
        
    }
    
    ~CQuadTree();
    
    
};

#endif