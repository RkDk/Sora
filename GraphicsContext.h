#ifndef GRAPHICSCONTEXT_H_
#define GRAPHICSCONTEXT_H_

#include <GL/glew.h>
#include "SDL.h"

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

	int m_WindowWidth, m_WindowHeight;

	void InitializeOpenGL();

public:

    void SetDrawContext( CDrawContext * pDrawContext )
    {

        m_pDrawContext = pDrawContext;

    }

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

	void ClearBuffer();
	void SwapBuffers();

	void SetDrawMode( int );

	void CreateHandle( std::string, int, int, int, int, bool );
	void CreateHandle( std::string );

	int LoadShaderProgram( std::string, std::string );

	int GetShaderIDFromIndex( int i )
	{

	    return m_pShaderPrograms[i].GetProgramID();

	}

	CGraphicsContext() : m_pWndHandle( NULL ), m_pSDLRenderer( NULL ), m_pDrawContext( NULL )
	{

	}

	~CGraphicsContext();

};

#endif
