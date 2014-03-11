#ifndef TEXTUREIMAGE_H_
#define TEXTUREIMAGE_H_

#include <GL/glew.h>
#include "SDL_image.h"
#include <string>

#include "Logging.h"

class CTextureImage
{

private:

	int m_FrameWidth, m_FrameHeight;
	GLuint m_Texture;

	void Load( std::string );

public:

    void Bind();

	~CTextureImage();

};

#endif
