#include "QuadTree.h"

void CQuadTree::Init( int x, int y, int size, int layer ) {

    m_Pos.Set( x, y );
    m_Size.Set( size, size );
    m_CurLayer = layer;
    
    if( size > MINIMUM_QT_SIZE ) {
    
        m_pChildNodes = new CQuadTree[4];
        
        for( int i = 0; i < 2; i++ ) {
         
            for( int j = 0; j < 2; j++ ) {
                
                m_pChildNodes[j+i*2].Init( x + j * ( size / 2 ), y + i * ( size / 2 ), size / 2, layer + 1 );
                m_pChildNodes[j+i*2].m_pParentNode = this;
                
            }
            
        }
        
    }

}

void CQuadTree::Draw( CDrawContext * pDrawContext ) {
    
    float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;
 
    if( !m_pChildNodes ) {
     
        if( !IsEmpty() ) {
         
            pDrawContext->DrawGLTexture( 0, m_Pos.GetX(), m_Pos.GetY(), m_Size.GetX(), m_Size.GetY(), 1.0f, 0.0f, 0.0f, .3f );
            
        }
        
    }
    
    pDrawContext->DrawGLTexture( 0, m_Pos.GetX(), m_Pos.GetY(), m_Size.GetX(), 2.0f, r, g, b, a );
    pDrawContext->DrawGLTexture( 0, m_Pos.GetX() + m_Size.GetX(), m_Pos.GetY(), 2.0f, m_Size.GetY(), r, g, b, a );
    pDrawContext->DrawGLTexture( 0, m_Pos.GetX(), m_Pos.GetY(), 2.0f, m_Size.GetY(), r, g, b, a );
    pDrawContext->DrawGLTexture( 0, m_Pos.GetX(), m_Pos.GetY() + m_Size.GetY(), m_Size.GetX(), 2.0f, r, g, b, a );
    
    if( m_pChildNodes ) {
     
        for( int i = 0; i < 4; i++ ) {
         
            m_pChildNodes[i].Draw( pDrawContext );
            
        }
        
    }
    
}

void CQuadTree::RemoveIfObjectHasMoved( CQuadTreeObject * obj ) {
    
    if( m_pChildNodes ) {
     
        float x, y, w, h;
        obj->GetPos( &x, &y );
        obj->GetSize( &w, &h );
        
        for( int i = 0; i < 4; i++ ) {
         
            if( m_pChildNodes[i].HasEntity( obj ) ) {
                
                if( !m_pChildNodes[i].ContainsSpace( x, y, w, h ) ) {
                 
                    m_pChildNodes[i].RemoveObject( obj, false );
                    
                } else {
                 
                    m_pChildNodes[i].RemoveIfObjectHasMoved( obj );
                    
                }
                
            }
            
        }
        
    }
    
    
}

void CQuadTree::InsertObject( CQuadTreeObject * obj ) {

    float x, y, w, h;
    
    obj->GetPos( &x, &y );
    obj->GetSize( &w, &h );
    
    if( ContainsSpace( x, y, w, h ) ) {
    
        m_pQTObjects.insert( std::make_pair( obj->GetEntityID(), obj ) );
 
        if( m_pChildNodes ) {
        
            for( int i = 0; i < 4; i++ ) {
             
                m_pChildNodes[i].InsertObject( obj );
                
            }
        
        }
        
    }
    
}

CQuadTreeObject * CQuadTree::AddEntity( CWorldEntity * e ) {
    
    CQuadTreeObject * o = new CQuadTreeObject( e );
    e->SetQuadTreeEntity( o );
    e->UpdateQuadTreeEntityPos();
    e->UpdateQuadTreeEntitySize();
    InsertObject( o );
    
    return o;
    
}

bool CQuadTree::HasEntity( CQuadTreeObject * e ) {
 
    return !( m_pQTObjects.end() == m_pQTObjects.find( e->GetEntityID() ) );
    
}

void CQuadTree::GetObjectsInLayer( std::vector< CNodeList > & results, int layer ) {
    
    if( m_CurLayer == layer || ( layer < 0 && !m_pChildNodes ) ) {
        
        if( m_pQTObjects.size() < 1 )
            return;
        
        CNodeList n( m_CurLayer );
        
        for( std::unordered_map<  int, CQuadTreeObject * >::iterator iter = m_pQTObjects.begin();
            iter != m_pQTObjects.end(); iter++ ) {
            
            CQuadTreeObject * p = iter->second;
            
            if( !p->GetShouldKill() ) {

                n.m_pNodeObjects.push_back( p );
                
            }
            
        }
        
        if( n.m_pNodeObjects.size() > 1 )
            results.push_back( n );
        
    } else if( m_CurLayer < layer ) {

        if( m_pChildNodes ) {
        
            for( int j = 0; j < 4; j ++ ) {
             
                m_pChildNodes[j].GetObjectsInLayer( results, layer );
                
            }
            
        }
        
    }
    
}



void CQuadTree::Think() {
 
    for( std::unordered_map< int, CQuadTreeObject * >::iterator iter = m_pQTObjects.begin();
        iter != m_pQTObjects.end(); ) {
     
        CQuadTreeObject * o = iter->second;
        
        if( o->GetShouldKill() ) {
        
            for( int i = 0; i < 4; i++ ) {
             
                m_pChildNodes[i].RemoveObject( o, false );
                
            }
            
            delete o;
            iter = m_pQTObjects.erase( iter );
            
        } else {
            
            iter++;
            
            if( o->GetShouldUpdate() ) {
         
                RemoveIfObjectHasMoved( o );
                InsertObject( o );
                    
                
            }
            
        }
        
    }
   
}

void CQuadTree::RemoveObject( CQuadTreeObject * pQuadTreeObject, bool deleteObj ) {

    std::unordered_map< int, CQuadTreeObject * >::iterator end = m_pQTObjects.end();
    std::unordered_map< int, CQuadTreeObject * >::iterator target = m_pQTObjects.find( pQuadTreeObject->GetEntityID() );
    
    if( target != end ) {
        
        if( m_pChildNodes ) {
            
            for( int j = 0; j < 4; j++ ) {
             
                m_pChildNodes[j].RemoveObject( pQuadTreeObject, deleteObj );
                
            }
            
        }
    
        m_pQTObjects.erase( target );
        
        if( !m_pParentNode && deleteObj ) {
            
            delete pQuadTreeObject;
            
        }


    }

    
}

void CQuadTree::Init( int x, int y, int size ) {

    Init( x, y, size, 1 );
    
}

CQuadTree::~CQuadTree() {

    if( m_CurLayer == 1 ) {
        
        for( std::unordered_map< int, CQuadTreeObject * >::iterator iter = m_pQTObjects.begin();
            iter != m_pQTObjects.end(); ) {
         
            delete iter->second;
            iter = m_pQTObjects.erase( iter );
            
        }
        
    }
    
    m_pQTObjects.clear();
    
}