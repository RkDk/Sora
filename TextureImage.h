#ifndef TEXTUREIMAGE_H_
#define TEXTUREIMAGE_H_

#include "Vector.h"
#include "SDL_includes.h"

#include <GL/glew.h>
#include <string>
#include <vector>

#include "Logging.h"

class CTextureFrame
{

private:

    Vector2< float > m_Offset;

 	int m_FrameWidth, m_FrameHeight;
 	int m_FrameDelay;
	GLuint m_Texture;

public:

    void Load( std::string );

    GLuint GetTexture()
    {

        return m_Texture;

    }

 	void GetSize( int * width, int * height ) const
	{

		*width = m_FrameWidth;
		*height = m_FrameHeight;

	}

	void SetDelay( int delay )
	{

	    m_FrameDelay = delay;

	}

	int GetDelay()
	{

	    return m_FrameDelay;

	}

	const Vector2< float > & GetOffset() const
	{

	    return m_Offset;

	}

	void SetOffset( Vector2< float > & o )
	{

	    m_Offset = o;

	}

	~CTextureFrame();

};

class CTextureImage
{

private:

    CTextureFrame * m_pFrames;
    int m_FrameCount;

public:

	CTextureFrame & GetFrame( int i )
	{

	    return m_pFrames[i];

	}

    int GetFrameDelay( int i ) const
    {

        return m_pFrames[i].GetDelay();

    }

	int GetFrameCount() const
	{

	    return m_FrameCount;

	}

	const Vector2< float > & GetFrameOffset( int i ) const
	{

	    return m_pFrames[i].GetOffset();

	}

	void GetFrameSize( int i, int * width, int * height ) const
	{

	    m_pFrames[i].GetSize( width, height );

	}

	void Load( std::string );

    void Bind( int );
    void Bind();

	~CTextureImage();

};

#endif
