/**
* @file GLContext.h
*/
#ifndef GLCONTEXT_H_INCLUDED
#define GLCONTEXT_H_INCLUDED
#include <glad/glad.h>

/// ŽOŽźŚłŤŔ•WŚ^.
struct Position
{
	float x, y, z;
};

/// RGBAJ‰[Ś^.
struct Color
{
	float r, g, b, a;
};

namespace GLContext {

	GLuint CreateBuffer(GLsizeiptr size, const GLvoid* data);
	GLuint CreateVertexArray(GLuint vboPosition, GLuint vboColor,
		GLuint vboTexcoord, GLuint vboNormal, GLuint ibo);
	GLuint CreateProgram(GLenum type, const GLchar* code);
	GLuint CreateProgramFromFile(GLenum type, const char* filename);
	GLuint CreatePipeline(GLuint vp, GLuint fp);
	GLuint CreateImage2D(GLsizei width, GLsizei height, const void* data,
		GLenum pixelFormat, GLenum type);
	GLuint CreateImage2D(const char* path);
	GLuint CreateSampler(GLenum wrapMode);

} // namespace GLContext

#endif // GLCONTEXT_H_INCLUDED