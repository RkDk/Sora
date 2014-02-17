#ifndef GRAPHICSCONTEXT_H_
#define GRAPHICSCONTEXT_H_

#include <GL/glew.h>
#include "SDL.h"

#include <string>
#include "DrawContext.h"
#include "Logging.h"
#include "ShaderProgram.h"

class CGraphicsContext
{

private:

	CDrawContext * m_pDrawContext;
	CShaderProgram * m_pCurShader;

	SDL_Window * m_pWndHandle;
	SDL_Renderer * m_pSDLRenderer;
	SDL_GLContext m_OGLContext;

	int m_WindowWidth, m_WindowHeight;

	void InitializeOpenGL();
	void CreateDrawContext();

public:

	CDrawContext * GetDrawContext()
	{

		return m_pDrawContext;

	}

	void ClearBuffer();
	void SwapBuffers();

	void CreateHandle( std::string, int, int, int, int, bool );
	void CreateHandle( std::string );

	void LoadShader( std::string, std::string );

	CGraphicsContext() : m_pWndHandle( NULL ), m_pSDLRenderer( NULL ), m_pDrawContext( NULL ), m_pCurShader( NULL )
	{

	}

	~CGraphicsContext();

};

#endif