#ifndef CAMERA_H_
#define CAMERA_H_

#include "Vector.h"

enum class CAMTYPE {
    
    BOX = 0,
    CENTER,
    NONE
    
};

class CCamera {
    
private:
    
    Vector2< float > m_TargetPos;
    Vector4< float > m_BoxBounds;
    CAMTYPE m_CameraType;
    
    Vector2< float > m_CameraUpperLeftPos;
    Vector2< float > m_CameraTranslate;
    
    bool m_bCameraFixed;
    
public:
    
    CCamera();
    
    void Translate( float x, float y ) {
        
        m_CameraUpperLeftPos.Set( m_CameraUpperLeftPos.GetX() + x, m_CameraUpperLeftPos.GetY() + y );
        
    }
    
    void SetCameraFixed( bool b ) {
        m_bCameraFixed = b;
    }
    
    void SetBoxBounds( float x1, float y1, float x2, float y2 ) {
        m_BoxBounds.Set( x1, y1, x2, y2 );
    }
    
    void SetTargetPos( float x, float y ) {
        m_TargetPos.Set( x, y );
    }
    
    void SetCameraType( CAMTYPE c ) {
        m_CameraType = c;
    }
    
    const Vector2< float > & GetTranslate() {
        
        return m_CameraTranslate;
        
    }
    
    void Think();
    
};

#endif
