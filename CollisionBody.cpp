#include "CollisionBody.h"

void CCollisionBody::FindSATMinMax( const std::vector< Vector3< float > > & colOffset, Vector3< float > & pos, Vector3< float > & axis, float * min, float * max ) {
    
    
    unsigned long int offsetCount = colOffset.size();
    float * d = new float[offsetCount];
    
    for( int j = 0; j < offsetCount; j++ ) {
        
        Vector3< float > np = colOffset[j] + pos;
        d[j] = np.GetDotProduct( axis );
        
    }
    
    *min = d[0];
    *max = d[0];
    
    for( int j = 1; j < offsetCount; j++ ) {
        
        if( d[j] < *min )
            *min = d[j];
        else if( d[j] > *max )
            *max = d[j];
        
    }
    
    delete [] d;
    

    
}


bool CCollisionBody::CheckSATCollision( CCollisionInfo & info, Vector3< float > & curPos, CCollisionBody * c, Vector3< float > & cPos ) {
    
    unsigned long int curAxisCount = m_Axis.size();
    unsigned long int totalAxisCount = curAxisCount + c->GetAxisCount();
    

    for( int j = 0; j < totalAxisCount; j++ ) {
        
        Vector3< float > curAxis = ( j >= curAxisCount )? c->GetAxis( j - curAxisCount ) : m_Axis[j];
        
        float minA, maxA;
        float minB, maxB;
        
        FindSATMinMax( m_ColOffset, curPos, curAxis, &minA, &maxA );
        FindSATMinMax( c->GetOffsets(), cPos, curAxis, &minB, &maxB );
        
        double d;
        
        if( minA < minB )
            d = minB - maxA;
        else
            d = minA - maxB;
        
        if( d > 0 ) {
            
            
            return false;
            
            
        } else {
            
            if( fabs( d ) < info.minTransDist ) {
                
                info.minTransDist = fabs( d );
                
                if( minA < minB )
                    info.minTransAxis = curAxis * -1.0;
                else
                    info.minTransAxis = curAxis;
                
                
            }
            
        }
        
    }
    
    info.collision = true;
    
    return true;

}