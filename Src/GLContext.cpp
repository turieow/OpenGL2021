/*
*	@file GLContext.cpp
*/
#include "GLContext.h"

/*
*	OpenGL�R���e�L�X�g�Ɋւ���@�\���i�[���閼�O���
*/
namespace GLContext
{
	// �o�b�t�@�I�u�W�F�N�g���쐬����
	GLuint CreateBuffer(GLsizeiptr size, const GLvoid* data)
	{
		GLuint id = 0;
		glCreateBuffers(1, &id);
		glNamedBufferStorage(id, size, data, 0);
		return id;
	}

	// Vertex Array Object���쐬����
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