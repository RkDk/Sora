#ifndef SHADERPROGRAM_H_
#define SHADERPROGRAM_H_

#include "GL/glew.h"
#include <string>
#include "Logging.h"
#include "FileUtil.h"

class CShaderProgram
{

private:

	GLuint m_ProgramID;

	GLuint GetShader( int, std::string );

public:

	GLuint GetProgramID()
	{

		return m_ProgramID;

	}

	void Load( std::string, std::string );

	~CShaderProgram();

};

#endif
