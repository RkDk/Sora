#include "TextureImage.h"
#include <sstream>


CTextureFrame::~CTextureFrame()
{
    
    if( m_pData ) {
    
        delete [] m_pData;

        glDeleteTextures( 1, &m_Texture );

    }
        
}


void CTextureFrame::Load( std::string file )
{

    SDL_Surface * i = IMG_Load( file.c_str() );

    if( i == NULL )
    {

            Log::Error( "Failed loading material: " + file );
            return;


    } else
            Log::Log( "Successfully loaded material: " + file );

    m_Path = file;
    
    int bpp = i->format->BytesPerPixel;
    int rgbtype = GL_RGBA;
    int fmt = 0;

    bool bmask = false;

    if( i->format->Rmask != 0x000000ff )
            bmask = true;

    if( bpp == 4 )
    {

        if( bmask )
                fmt = GL_BGRA;
        else
                fmt = GL_RGBA;

    } else
    {
        
        rgbtype = GL_RGB;

        if( bmask )
                fmt = GL_BGR;
        else
                fmt = GL_RGB;

    }

    glGenTextures( 1, &m_Texture );
    glBindTexture( GL_TEXTURE_2D, m_Texture );
  

    glTexImage2D( GL_TEXTURE_2D, 0, rgbtype, i->w, i->h, 0, fmt, GL_UNSIGNED_BYTE, i->pixels );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

    m_FrameWidth = i->w;
    m_FrameHeight = i->h;
    m_BytesPerPixel = bpp;
    
    int size = m_FrameWidth * m_FrameHeight * m_BytesPerPixel;
    
    m_pData = new GLubyte[size];
    
    for( int j = 0; j < size; j++ )
        m_pData[j] = ( ( GLubyte * )( i->pixels ) )[j];
    
    
    SDL_FreeSurface( i );


}

CTextureImage::~CTextureImage()
{

	if( m_pFrames )
		delete [] m_pFrames;

}

void CTextureImage::Bind( int i )
{

    glBindTexture( GL_TEXTURE_2D, m_pFrames[i].GetTexture() );

}

void CTextureImage::Bind()
{

    Bind( 0 );

}


void CTextureImage::Load( std::string file )
{


    std::vector< std::string > spriteframes;
    std::vector< int > spritedelay;
    std::vector< Vector2< float > > spriteoffset;

    m_Path = file;
    
    if( file.find( ".txt" ) != std::string::npos )
    {

        std::ifstream spritefile( file.c_str() );

        do
        {

            std::string temp;

            spritefile >> temp;

            if( temp != "END" )
            {

                int delay = 0;
                float x = 0.0f, y = 0.0f;

                spritefile >> delay >> x >> y;

                spriteframes.push_back( temp );
                spritedelay.push_back( delay );
                spriteoffset.push_back( Vector2< float >( x, y ) );


            } else
                break;

        } while( 1 );
        

    } else
    {

        spriteframes.push_back( file );
        spritedelay.push_back( 0 );
        spriteoffset.push_back( Vector2< float >() );

    }

    m_FrameCount = spriteframes.size();
    m_pFrames = new CTextureFrame[m_FrameCount];

    for( int j = 0; j < m_FrameCount; j++ )
    {

        m_pFrames[j].Load( spriteframes[j] );
        m_pFrames[j].SetDelay( spritedelay[j] );
        m_pFrames[j].SetOffset( spriteoffset[j] );

    }

}

