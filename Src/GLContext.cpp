/*
*	@file GLContext.cpp
*/
#include "GLContext.h"

/*
*	OpenGLコンテキストに関する機能を格納する名前空間
*/
namespace GLContext
{
	// バッファオブジェクトを作成する
	GLuint CreateBuffer(GLsizeiptr size, const GLvoid* data)
	{
		GLuint id = 0;
		glCreateBuffers(1, &id);
		glNamedBufferStorage(id, size, data, 0);
		return id;
	}

	// Vertex Array Objectを作成する
	GLuint CreateVertexArray(GLuint vboPosition, GLuint vboColor)
	{
		GLuint id = 0;
		glCreateVertexArrays(1, &id);

		const GLuint positionIndex = 0;
		const GLuint positionBindingIndex = 0;
		glEnableVertexArrayAttrib(id, positionIndex);
		glVertexArrayAttribFormat(id, positionIndex, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(id, positionIndex, positionBindingIndex);
		glVertexArrayVertexBuffer(
			id, positionBindingIndex, vboPosition, 0, sizeof(Position));

		return id;
	}
} // namespace GLContext