#ifndef TEXTUREIMAGE_H_
#define TEXTUREIMAGE_H_

#include <GL/glew.h>
#include "SDL_image.h"
#include <string>
#include <vector>

#include "Logging.h"

class CTextureFrame
{

private:

 	int m_FrameWidth, m_FrameHeight;
 	int m_FrameDelay;
	GLuint m_Texture;

public:

    void Load( std::string );

    GLuint GetTexture()
    {

        return m_Texture;

    }

 	void GetSize( int * width, int * height )
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

    int GetFrameDelay( int i )
    {

        return m_pFrames[i].GetDelay();

    }

	int GetFrameCount()
	{

	    return m_FrameCount;

	}

	void GetFrameSize( int i, int * width, int * height )
	{

	    m_pFrames[i].GetSize( width, height );

	}

	void Load( std::string );
    void Bind( int );

	~CTextureImage();

};

#endif
