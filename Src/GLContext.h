#pragma once
/*
*	@file GLContext.h
*/
#ifndef  GLCONTEXT_H_INCLUDED
#define GLCONTEXT_H_INCLUDED
#include<glad/glad.h>

/// �O�������W�^
struct Position
{
	float x, y, z;
};

/// RGBA�J���[�^
struct Color
{
	float r, g, b, a;
};

namespace GLContext
{
	GLuint CreateBuffer(GLsizeiptr size, const GLvoid* data);
	GLuint CreateVErtexArray(GLuint vboPosition, GLuint vboColor);
}// namespace GLContext

#endif // ! GLCONTEXT_H_INCLUDED
