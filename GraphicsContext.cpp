#include "GraphicsContext.h"

CGraphicsContext::~CGraphicsContext()
{


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

int CGraphicsContext::LoadShaderProgram( std::string vertexfile, std::string fragfile )
{

	Log::Debug( "Loading shader" );

	CShaderProgram * pShader = new CShaderProgram;
	pShader->Load( vertexfile, fragfile );

	Log::Debug( "Shader loaded" );

	m_pShaderPrograms.push_back( pShader );

	return pShader->GetProgramID();

}

void CGraphicsContext::InitializeOpenGL()
{

	Log::Debug( "Initializing OpenGL" );

	m_OGLContext = SDL_GL_CreateContext( m_pWndHandle );

	glViewport( 0, 0, m_WindowWidth, m_WindowHeight );

	glEnable( GL_TEXTURE_2D );

	glShadeModel( GL_SMOOTH );

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glEnable( GL_COLOR_MATERIAL );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	glewInit();

}

void CGraphicsContext::SetDrawMode( int mode )
{

    glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

    switch( mode )
    {

    case DRAW_MODE_2D:
        gluOrtho2D( 0, m_WindowWidth, m_WindowHeight, 0 );
        break;
    case DRAW_MODE_3D:
    default:
        //Insert 3d code
        break;

    }


	glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();

}

void CGraphicsContext::GetWindowSize( int * width, int * height )
{

    *width = m_WindowWidth;
    *height = m_WindowHeight;

}

void CGraphicsContext::CreateHandle( std::string wndTitle )
{

	CreateHandle( wndTitle, 0, 0, 0, 0, true );

}

void CGraphicsContext::CreateHandle( std::string wndTitle, int x, int y, int width, int height, bool fullscreen )
{

	Log::Debug( "Creating windows handle" );

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

}
