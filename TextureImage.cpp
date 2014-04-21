#include "TextureImage.h"

CTextureFrame::~CTextureFrame()
{

    glDeleteTextures( 1, &m_Texture );

}


void CTextureFrame::Load( std::string file )
{

    SDL_Surface * i = IMG_Load( file.c_str() );

    if( i == NULL )
    {

            Log::Log( "Failed loading material: " + file );
            return;


    } else
            Log::Log( "Successfully loaded material: " + file );

    int bpp = i->format->BytesPerPixel;
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

            if( bmask )
                    fmt = GL_BGR;
            else
                    fmt = GL_RGB;

    }

    glGenTextures( 1, &m_Texture );
    glBindTexture( GL_TEXTURE_2D, m_Texture );

    glTexImage2D( GL_TEXTURE_2D, 0, bpp, i->w, i->h, 0, fmt, GL_UNSIGNED_BYTE, i->pixels );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    m_FrameWidth = i->w;
    m_FrameHeight = i->h;

    SDL_FreeSurface( i );


}

CTextureImage::~CTextureImage()
{

	delete [] m_pFrames;

}

void CTextureImage::Bind( int i )
{

    glBindTexture( GL_TEXTURE_2D, m_pFrames[i].GetTexture() );

}

void CTextureImage::Load( std::string file )
{

    std::vector< std::string > frameFiles;

    if( file.find( ".txt" ) != std::string::npos )
    {

        //Read sprite file

    } else
    {

        frameFiles.push_back( file );
        m_FrameCount = 1;

    }

    m_pFrames = new CTextureFrame[m_FrameCount];

    for( int j = 0; j < m_FrameCount; j++ )
        m_pFrames[j].Load( frameFiles[j] );

}

