#ifndef INSTANCEDPARTICLEENGINE_H_
#define INSTANCEDPARTICLEENGINE_H_

#include "GL/glew.h"
#include "Matrix.h"
#include "Vector.h"

#include <algorithm>
#include <vector>

class CInstancedParticleEngine {
  
private:

    int m_MaxParticles, m_ShaderOffset;
    
    GLuint m_VertexArray;
    GLuint m_InstancedBuffer, m_InstancedRGBABuffer;
    
    std::vector< Vector2< float > > m_Size;
    
    float m_Width, m_Height;
    float * m_ViewMat;
    float * m_Color;
    
public:
    
    void Init( int, int );
    void InitShader( int );
    
    void BindVertexBuffers();
    void BindVertexBuffers( bool, bool );
    
    void SetParticlePos( int, float, float );
    void SetParticleSize( int, float, float );
    void SetParticleColor( int, float, float, float, float );
    
    void Draw();
    
    ~CInstancedParticleEngine();
    
};

#endif
