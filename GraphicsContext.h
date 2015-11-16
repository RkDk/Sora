#ifndef GRAPHICSCONTEXT_H_
#define GRAPHICSCONTEXT_H_

#include "SDL_includes.h"

#include <GL/glew.h>

#include <boost/ptr_container/ptr_vector.hpp>
#include <string>
#include "DrawContext.h"
#include "Logging.h"
#include "ShaderProgram.h"

enum DrawMode
{

    DRAW_MODE_2D = 1,
    DRAW_MODE_3D

};

class CGraphicsContext
{

private:

	CDrawContext * m_pDrawContext;
	boost::ptr_vector< CShaderProgram > m_pShaderPrograms;

	SDL_Window * m_pWndHandle;
	SDL_Renderer * m_pSDLRenderer;
	SDL_GLContext m_OGLContext;
	bool m_bFullScreen;

    Vector4< float > m_ClearColor;
    
	int m_WindowWidth, m_WindowHeight;

	void InitializeOpenGL();

public:
    
    int GetShaderCount() {
    
        return m_pShaderPrograms.size();
    
    }
    
    void UseShader( int );

    void SetDrawContext( CDrawContext * pDrawContext )
    {

        m_pDrawContext = pDrawContext;

    }

	bool IsFullScreen() { 
	
		return m_bFullScreen;

	}

	void SetFullScreen( bool );

	CDrawContext * GetDrawContext()
	{

		return m_pDrawContext;

	}

	void GetWindowSize( int *, int * );

	int GetWindowWidth()
	{

	    return m_WindowWidth;

	}

	int GetWindowHeight()
	{

	    return m_WindowHeight;

	}
    
    void SetClearColor( float, float, float, float );

	void ClearBuffer();
	void SwapBuffers();

	void SetDrawMode( int );

	void CreateHandle( std::string, int, int, int, int, bool );
	void CreateHandle( std::string );

	int LoadShaderProgram( std::string, std::string );

    int GetShaderUniformLocation( int i, std::string name ) {
        
        return glGetUniformLocation( m_pShaderPrograms[i].GetProgramID(), name.c_str() );
        
    }
    
	int GetShaderIDFromIndex( int i )
	{

	    return m_pShaderPrograms[i].GetProgramID();

	}

	CGraphicsContext() : m_pWndHandle( NULL ), m_pSDLRenderer( NULL ), m_pDrawContext( NULL ), m_bFullScreen( false )
	{

	}

	~CGraphicsContext();

};

#endif
