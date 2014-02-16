#include "GraphicsContext.h"

CGraphicsContext::~CGraphicsContext()
{

	delete m_pDrawContext;
	delete m_pCurShader;

	SDL_GL_DeleteContext( m_OGLContext );
	SDL_DestroyRenderer( m_pSDLRenderer );
	SDL_DestroyWindow( m_pWndHandle );


}

void CGraphicsContext::ClearBuffer()
{

	glClearColor( 0, 0, 0, 1 );
	glClear( GL_COLOR_BUFFER_BIT );

}

void CGraphicsContext::SwapBuffers()
{

	SDL_GL_SwapWindow( m_pWndHandle );

}

void CGraphicsContext::LoadShader( std::string vertexfile, std::string fragfile )
{

	m_pCurShader = new CShaderProgram;
	m_pCurShader->Load( vertexfile, fragfile );

	glUseProgram( m_pCurShader->GetProgramID() );

}

void CGraphicsContext::CreateDrawContext()
{

	m_pDrawContext = new CDrawContext;

}

void CGraphicsContext::InitializeOpenGL()
{

	m_OGLContext = SDL_GL_CreateContext( m_pWndHandle );
 
	glViewport( 0, 0, m_WindowWidth, m_WindowHeight );

	glMatrixMode( GL_PROJECTION );
	glLoadIdentity();
 
	gluOrtho2D( 0, m_WindowWidth, m_WindowHeight, 0 );

	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
 
	glEnable( GL_TEXTURE_2D );
 
	glShadeModel( GL_SMOOTH );
 
	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );
 
	glEnable( GL_DEPTH_TEST );
	glDepthFunc( GL_LEQUAL );
 
	glClearColor( 0.1f, 0.1f, 0.1f, 0.0f );
	glClearDepth( 1.0f );
 
	glEnable( GL_COLOR_MATERIAL );
 
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );
 
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );
                
	glewInit();

}

void CGraphicsContext::CreateHandle( std::string wndTitle )
{

	CreateHandle( wndTitle, 0, 0, 0, 0, true );

}

void CGraphicsContext::CreateHandle( std::string wndTitle, int x, int y, int width, int height, bool fullscreen )
{

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{

		Log::Log( "Initializing SDL has failed" );
		return;

	}

	if( x <= 0 )
		x = SDL_WINDOWPOS_UNDEFINED;

	if( y <= 0 )
		y = SDL_WINDOWPOS_UNDEFINED;

	int flags = SDL_WINDOW_OPENGL;

	if( fullscreen )
		flags |= SDL_WINDOW_FULLSCREEN;
 
	if( !( m_pWndHandle = SDL_CreateWindow( wndTitle.c_str(), x, y, width, height, flags ) ) )
	{

		Log::Log( "Creating SDL Window handle has failed" );
		return;
   
	}

	SDL_GetWindowSize( m_pWndHandle, &m_WindowWidth, &m_WindowHeight );

	InitializeOpenGL();

	CreateDrawContext();

}