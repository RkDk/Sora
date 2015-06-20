#include "GraphicsContext.h"
#include <sstream>

CGraphicsContext::~CGraphicsContext()
{


	SDL_GL_DeleteContext( m_OGLContext );
	SDL_DestroyRenderer( m_pSDLRenderer );
	SDL_DestroyWindow( m_pWndHandle );


}

void CGraphicsContext::SetClearColor( float r, float g, float b, float a ) {
 
    m_ClearColor.Set( r, g, b, a );
    
}

void CGraphicsContext::ClearBuffer()
{

	glClearColor( m_ClearColor.GetX(), m_ClearColor.GetY(), m_ClearColor.GetZ(), m_ClearColor.GetW() );
	glClear( GL_COLOR_BUFFER_BIT );

}

void CGraphicsContext::SwapBuffers()
{

	SDL_GL_SwapWindow( m_pWndHandle );

}

int CGraphicsContext::LoadShaderProgram( std::string vertexfile, std::string fragfile )
{

	Log::Log( "Loading shaders: " + vertexfile + ", " + fragfile );

	CShaderProgram * pShader = new CShaderProgram;
	pShader->Load( vertexfile, fragfile );

	Log::Log( "Shaders loaded" );

	m_pShaderPrograms.push_back( pShader );

	return pShader->GetProgramID();

}

void CGraphicsContext::InitializeOpenGL()
{


	Log::Log( "Initializing OpenGL" );

	m_OGLContext = SDL_GL_CreateContext( m_pWndHandle );

    m_ClearColor.Set( 0.0f, 0.0f, 0.0f, 1.0f );
    
	glViewport( 0, 0, m_WindowWidth, m_WindowHeight );

	glEnable( GL_TEXTURE_2D );

	glShadeModel( GL_SMOOTH );

	glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

	glEnable( GL_COLOR_MATERIAL );

	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

    #ifdef __APPLE__
        glewExperimental = GL_TRUE;
    #endif
	
    glewInit();

}

void CGraphicsContext::UseShader( int i ) {
 
    if( m_pDrawContext ) {
        
        m_pDrawContext->UseShaderProgram( GetShaderIDFromIndex( i ) );
        m_pDrawContext->Bind2DVertexBuffer();
        
    }
    
}

void CGraphicsContext::SetDrawMode( int mode )
{
    

    glMatrixMode( GL_PROJECTION );
	glLoadIdentity();

    switch( mode )
    {

    case DRAW_MODE_2D:
        glOrtho( 0, m_WindowWidth, m_WindowHeight, 0, -1, 1 );
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

void CGraphicsContext::SetFullScreen( bool b ) {

	if( m_pWndHandle ) {
	
		m_bFullScreen = b;
		Uint32 flags = ( b )? SDL_WINDOW_FULLSCREEN : 0;

		if( SDL_SetWindowFullscreen( m_pWndHandle, flags ) < 0 ) {
		
			std::stringstream ss;
			ss << "Failed to toggle between window/fullscreen because: " << SDL_GetError();
			Log::Debug( ss.str() );
		
		} else
			Log::Debug( "Successfully toggled between window/fullscreen" );
	}

}

void CGraphicsContext::CreateHandle( std::string wndTitle, int x, int y, int width, int height, bool fullscreen )
{

	Log::Log( "Creating windows handle" );

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{

		Log::Error( "Initializing SDL has failed" );
		return;

	}

    #ifdef __APPLE__
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    #endif

	if( x <= 0 )
		x = SDL_WINDOWPOS_UNDEFINED;

	if( y <= 0 )
		y = SDL_WINDOWPOS_UNDEFINED;

	int flags = SDL_WINDOW_OPENGL;

	if( fullscreen ) 
		flags |= SDL_WINDOW_FULLSCREEN;

	m_bFullScreen = fullscreen;

	if( !( m_pWndHandle = SDL_CreateWindow( wndTitle.c_str(), x, y, width, height, flags ) ) )
	{

		Log::Error( "Creating SDL Window handle has failed" );
		return;

	}

	SDL_GetWindowSize( m_pWndHandle, &m_WindowWidth, &m_WindowHeight );

	InitializeOpenGL();

	if( m_pDrawContext )
		m_pDrawContext->Initialize();

}
