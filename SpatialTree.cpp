#include "SpatialTree.h"
#include <sstream>
void CSpatialTree::RemoveIfObjectHasMoved( CSpatialTreeObject * obj ) {
    
    if( m_pChildNodes ) {
        
        for( int i = 0; i < m_NumNodes; i++ ) {
         
            if( m_pChildNodes[i].HasEntity( obj ) ) {
                
                if( !m_pChildNodes[i].ContainsObject( obj ) ) {
                 
                    m_pChildNodes[i].RemoveObject( obj, false );
                    
                } else {
                 
                    m_pChildNodes[i].RemoveIfObjectHasMoved( obj );
                    
                }
                
            }
            
        }
        
    }
    
    
}

void CSpatialTree::InsertObject( CSpatialTreeObject * obj ) {

    if( ContainsObject( obj ) || !m_pParentNode ) {
    
        m_pQTObjects.insert( std::make_pair( obj->GetEntityID(), obj ) );
 
        if( m_pChildNodes ) {
        
            for( int i = 0; i < m_NumNodes; i++ ) {
             
                m_pChildNodes[i].InsertObject( obj );
                
            }
        
        }
        
    }
    
}

CSpatialTreeObject * CSpatialTree::AddEntity( CWorldEntity * e ) {
    
    CSpatialTreeObject * o = new CSpatialTreeObject( e );
    e->SetSpatialTreeEntity( o );
    e->UpdateSpatialTreeEntityPos();
    e->UpdateSpatialTreeEntitySize();
    InsertObject( o );
    
    return o;
    
}

bool CSpatialTree::HasEntity( CSpatialTreeObject * e ) {
 
    return !( m_pQTObjects.end() == m_pQTObjects.find( e->GetEntityID() ) );
    
}

void CSpatialTree::GetObjectsInLayer( std::vector< CNodeList > & results, int layer ) {
    
    if( m_CurLayer == layer || ( layer < 0 && !m_pChildNodes ) ) {
        
        if( m_pQTObjects.size() < 1 )
            return;
        
        CNodeList n( m_CurLayer );
        
        for( std::unordered_map<  int, CSpatialTreeObject * >::iterator iter = m_pQTObjects.begin();
            iter != m_pQTObjects.end(); iter++ ) {
            
            CSpatialTreeObject * p = iter->second;
            
            if( !p->GetShouldKill() ) {

                n.m_pNodeObjects.push_back( p );
                
            }
            
        }
        
        if( n.m_pNodeObjects.size() > 1 )
            results.push_back( n );
        
    } else if( m_CurLayer < layer || layer < 0 ) {

        if( m_pChildNodes ) {
        
            for( int j = 0; j < m_NumNodes; j ++ ) {
             
                m_pChildNodes[j].GetObjectsInLayer( results, layer );
                
            }
            
        }
        
    }
    
}



void CSpatialTree::Think() {
 
    for( std::unordered_map< int, CSpatialTreeObject * >::iterator iter = m_pQTObjects.begin();
        iter != m_pQTObjects.end(); ) {
     
        CSpatialTreeObject * o = iter->second;
        
        if( o->GetShouldKill() ) {
        
            for( int i = 0; i < m_NumNodes; i++ ) {
             
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

void CSpatialTree::RemoveObject( int entID, bool deleteObj ) {
    
    std::unordered_map< int, CSpatialTreeObject * >::iterator end = m_pQTObjects.end();
    std::unordered_map< int, CSpatialTreeObject * >::iterator target = m_pQTObjects.find( entID );
    
    if( target != end ) {
        
        if( m_pChildNodes ) {
            
            for( int j = 0; j < m_NumNodes; j++ ) {
                
                m_pChildNodes[j].RemoveObject( entID, deleteObj );
                
            }
            
        }
        
        CSpatialTreeObject * pSpatialTreeObject = target->second;
        m_pQTObjects.erase( target );
        
        if( !m_pParentNode && deleteObj ) {
            
            delete pSpatialTreeObject;
            
        }
        
        
    }
    
    
}

void CSpatialTree::RemoveObject( CSpatialTreeObject * pSpatialTreeObject, bool deleteObj ) {

    RemoveObject( pSpatialTreeObject->GetEntityID(), deleteObj );
    
    /* defunct
    std::unordered_map< int, CSpatialTreeObject * >::iterator end = m_pQTObjects.end();
    std::unordered_map< int, CSpatialTreeObject * >::iterator target = m_pQTObjects.find( pSpatialTreeObject->GetEntityID() );
    
    if( target != end ) {
        
        if( m_pChildNodes ) {
            
            for( int j = 0; j < m_NumNodes; j++ ) {
             
                m_pChildNodes[j].RemoveObject( pSpatialTreeObject, deleteObj );
                
            }
            
        }
    
        m_pQTObjects.erase( target );
        
        if( !m_pParentNode && deleteObj ) {
            
            delete pSpatialTreeObject;
            
        }


    }
    */

    
}

CSpatialTree::~CSpatialTree() {

    if( m_CurLayer == 1 ) {
        
        for( std::unordered_map< int, CSpatialTreeObject * >::iterator iter = m_pQTObjects.begin();
            iter != m_pQTObjects.end(); ) {
         
            delete iter->second;
            iter = m_pQTObjects.erase( iter );
            
        }
        
    }
    
    m_pQTObjects.clear();
    
}


void CSpatialOctree::Draw( CDrawContext * pDrawContext ) {
    
    
}


void CSpatialOctree::CreateTree( int px, int py, int pz, int size, int layer ) {

	m_Pos.Set( px, py, pz );
	m_Size.Set( size, size, size );

	int halfsize = size / 2;
	m_CurLayer = layer;


	if( size > MINIMUM_QT_SIZE ) {

		m_pChildNodes = new CSpatialOctree[4];

		for( int z = 0; z < 2; z++ ) {

			for( int y = 0; y < 2; y++ ) {
		
				for( int x = 0; x < 2; x++ ) {
			
					CSpatialOctree * ocNodes = static_cast< CSpatialOctree * > ( m_pChildNodes );
					ocNodes[x + y * 2 + z * 4].CreateTree( halfsize * x, halfsize * y, halfsize * z, halfsize, layer + 1 );
					ocNodes[x + y * 2 + z * 4].m_pParentNode = this;

				}
		
			}

		}

	}

}

void CSpatialQuadTree::Draw( CDrawContext * pDrawContext, float cx, float cy ) {

    
    //float r = 1.0f, g = 1.0f, b = 1.0f, a = 1.0f;
    
    if( !m_pChildNodes ) {
        
        float x = m_Pos.GetX() + cx;
        float y = m_Pos.GetY() + cy;
        
        if( ContainsEntityCount( 1 ) ) {
            
            pDrawContext->DrawGLTexture( 0, x, y, m_Size.GetX(), m_Size.GetY(), 1.0f, 0.0f, 0.0f, .3f );
            
        } else
            pDrawContext->DrawGLTexture( 0, x, y, m_Size.GetX(), m_Size.GetY(), 0.0f, 0.0f, 1.0f, .3f );
        
    }
    
    //pDrawContext->DrawGLTexture( 0, m_Pos.GetX(), m_Pos.GetY(), m_Size.GetX(), 2.0f, r, g, b, a );
    //pDrawContext->DrawGLTexture( 0, m_Pos.GetX() + m_Size.GetX(), m_Pos.GetY(), 2.0f, m_Size.GetY(), r, g, b, a );
    //pDrawContext->DrawGLTexture( 0, m_Pos.GetX(), m_Pos.GetY(), 2.0f, m_Size.GetY(), r, g, b, a );
    //pDrawContext->DrawGLTexture( 0, m_Pos.GetX(), m_Pos.GetY() + m_Size.GetY(), m_Size.GetX(), 2.0f, r, g, b, a );
    
    if( m_pChildNodes ) {
        
        for( int i = 0; i < 4; i++ ) {
            
            m_pChildNodes[i].Draw( pDrawContext, cx, cy );
            
        }
        
    }
    


}

void CSpatialQuadTree::CreateTree( int px, int py, int size, int layer ) {

	m_Pos.Set( px, py );
	m_Size.Set( size, size );

	int halfsize = size / 2;
	m_CurLayer = layer;
    
    m_NumNodes = 4;

	if( size > MINIMUM_QT_SIZE ) {

		m_pChildNodes = new CSpatialQuadTree[4];

		for( int y = 0; y < 2; y++ ) {
		
			for( int x = 0; x < 2; x++ ) {
			
				CSpatialQuadTree * qtNodes = static_cast< CSpatialQuadTree * > ( m_pChildNodes );
				qtNodes[x + y * 2].CreateTree( px + x * halfsize, py + y * halfsize, halfsize, layer + 1 );
				qtNodes[x + y * 2].m_pParentNode = this;

			}
		
		}

	}

}
