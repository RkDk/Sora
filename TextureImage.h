#ifndef TEXTUREIMAGE_H_
#define TEXTUREIMAGE_H_

#include <GL/glew.h>
#include "SDL_image.h"
#include <string>

#include "Logging.h"

class CTextureFrame
{

private:

 	int m_FrameWidth, m_FrameHeight;
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

	int GetFrameCount()
	{

	    return m_FrameCount;

	}

	void Load( std::string );
    void Bind( int );

	~CTextureImage();

};

#endif
