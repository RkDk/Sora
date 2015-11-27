#include "Camera.h"

CCamera::CCamera() {
    
    m_CameraType = CAMTYPE::NONE;
    m_bCameraFixed = false;
    
}


void CCamera::Think() {
    
    if( !m_bCameraFixed ) {
        
        switch( m_CameraType ) {
                
            case CAMTYPE::CENTER: {
             
                break;
            }
            
            case CAMTYPE::BOX: {
                
                Vector2< float > targetScreenPos( m_CameraTranslate.GetX() + m_TargetPos.GetX(), m_CameraTranslate.GetY() + m_TargetPos.GetY() );
                
                if( targetScreenPos.GetX() < m_BoxBounds.GetX() ) {
                    
                    m_CameraUpperLeftPos.SetX( m_TargetPos.GetX() - m_BoxBounds.GetX() );
                    
                }
                
                
                if( targetScreenPos.GetY() < m_BoxBounds.GetY() ) {
                    
                    m_CameraUpperLeftPos.SetY( m_TargetPos.GetY() - m_BoxBounds.GetY() );
                    
                }
                

                if( targetScreenPos.GetX() > m_BoxBounds.GetZ() ) {
                    
                    m_CameraUpperLeftPos.SetX( m_TargetPos.GetX() - m_BoxBounds.GetZ() );
                    
                }

                if( targetScreenPos.GetY() > m_BoxBounds.GetW() ) {
                    
                    m_CameraUpperLeftPos.SetY( m_TargetPos.GetY() - m_BoxBounds.GetW() );
                    
                }

                
                break;
            }
                
            default:
                break;
                
                
        }
        
    }
    
    m_CameraTranslate.Set( ( int )-m_CameraUpperLeftPos.GetX(), ( int )-m_CameraUpperLeftPos.GetY() );
    
}