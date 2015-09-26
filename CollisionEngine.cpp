#include "CollisionEngine.h"

void CCollisionEngine::CheckForQuadTreeCollisions( CSpatialTree * pQuadTree, CCollisionListener * pListener ) {
    
    std::vector< CNodeList > nodeList;
    
    pQuadTree->GetObjectsInLayer( nodeList, -1 );

    for( std::vector< CNodeList >::iterator nodeListIter = nodeList.begin();
        nodeListIter != nodeList.end(); nodeListIter++ ) {
     
        CNodeList & nodeList = ( *nodeListIter );
        for( std::vector< CSpatialTreeObject * >::iterator nodeObjIter = nodeList.m_pNodeObjects.begin();
            nodeObjIter != nodeList.m_pNodeObjects.end(); ) {
         
            for( std::vector< CSpatialTreeObject * >::iterator nodeObjIter2 = ++nodeList.m_pNodeObjects.begin();
                nodeObjIter2 != nodeList.m_pNodeObjects.end(); nodeObjIter2++ ) {
                
                CSpatialTreeObject * qtObj1 = ( *nodeObjIter );
                CSpatialTreeObject * qtObj2 = ( *nodeObjIter2 );
                
                CWorldEntity * ent1 = qtObj1->GetEntity();
                CWorldEntity * ent2 = qtObj2->GetEntity();
                
                CCollisionBody * colBody1 = ent1->GetCollisionBody();
                CCollisionBody * colBody2 = ent2->GetCollisionBody();
                
                if( colBody1 && colBody2 ) {
                
                    Vector3< float > ent1Pos = Vector3< float >( ent1->GetX(), ent1->GetY(), 0.0f );
                    Vector3< float > ent2Pos = Vector3< float >( ent2->GetX(), ent2->GetY(), 0.0f );
                    
                    CCollisionInfo colInfo;
                    
                    if( colBody1->CheckSATCollision( colInfo, ent1Pos, colBody2, ent2Pos ) ) {
                     
                        CCollisionContact contact;
                        contact.SetCollisionInfo( &colInfo );
                        contact.SetObjects( ent1, ent2 );
                        pListener->BeginContact( contact );
                        
                        
                    }
                    
                }
                
            }
            
            nodeObjIter = ( *nodeListIter ).m_pNodeObjects.erase( nodeObjIter );
                
            
        }
        
    }
    
}