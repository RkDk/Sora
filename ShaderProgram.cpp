#include "ShaderProgram.h"

CShaderProgram::~CShaderProgram()
{

	glDeleteProgram( m_ProgramID );

}

GLuint CShaderProgram::GetShader( int mode, std::string file )
{

	GLuint shader = glCreateShader( mode );

	std::string src = FileUtil::ReadContentIntoString( file );

	const char * c_src = src.c_str();

	glShaderSource( shader, 1, &c_src, NULL );

	glCompileShader( shader );

	GLint status;
	glGetShaderiv( shader, GL_COMPILE_STATUS, &status );

	if( status == GL_FALSE )
	{

		GLint log_len;
		glGetShaderiv( shader, GL_INFO_LOG_LENGTH, &log_len );

		GLchar * c = new GLchar[log_len + 1];

		glGetShaderInfoLog( shader, log_len, NULL, c );

		char * output = new char[log_len + 255];

		sprintf( output, "Error loading shader '%s':\n%s", file.c_str(), c );

		Log::Error( output );

		delete [] output;
		delete [] c;

	} else
	{

		Log::Log( "Successfully loaded shader: " + file );

	}


	return shader;

}

void CShaderProgram::Load( std::string vertexfile, std::string fragfile )
{

	GLuint vshader = GetShader( GL_VERTEX_SHADER, vertexfile );
	GLuint fshader = GetShader( GL_FRAGMENT_SHADER, fragfile );

	m_ProgramID = glCreateProgram();

	glAttachShader( m_ProgramID, vshader );
	glAttachShader( m_ProgramID, fshader );

	glLinkProgram( m_ProgramID );

	glDetachShader(m_ProgramID, vshader );
	glDetachShader( m_ProgramID, fshader );

	glDeleteShader( vshader );
	glDeleteShader( fshader );


}
