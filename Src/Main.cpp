//4.5 �o�b�t�@�E�I�u�W�F�N�g���o�C���f�B���O�E�|�C���g�ɐݒ肷��



/*
*	@file Main.cpp
*/
#include<glad/glad.h>
#include "GLContext.h"
#include<GLFW/glfw3.h>
#include <string>
#include <iostream>
#pragma comment(lib, "opengl32.lib")

// ���W�f�[�^
const Position positions[] =
{
	{-0.33f, -0.5f, 0.5f },
	{ 0.33f, -0.5f, 0.5f },
	{ 0.0f,  0.5f, 0.5f },
};

const Color colors[]
{
	{ 0.0f, 0.0f, 1.0f, 1.0f }, // ��
	{ 0.0f, 1.0f, 0.0f, 1.0f }, // ��
	{ 1.0f, 0.0f, 0.0f, 1.0f }, // ��
};

/* OpenGL����̃��b�Z�[�W����������
* @param source			���b�Z�[�W�̔��M�ҁiOpenGL�AWindows�A�V�F�[�_�[�Ȃǁj
* @param type			���b�Z�[�W�̎�ށi�G���[�A�x���Ȃǁj
* @param id				���b�Z�[�W����ʂɎ��ʂ���l
* @param severity		���b�Z�[�W�̏d�v�x�i���A���A��A�Œ�j
* @param lenght			���b�Z�[�W�̕������B�{���Ȃ烁�b�Z�[�W�͂O�I�[����Ă���
* @param message		���b�Z�[�W�{��
* @param userParam		�R�[���o�b�N�ݒ莞�Ɏw�肵���|�C���^
*/
void GLAPIENTRY DebugCallback(GLenum source, GLenum type, GLuint id,
	GLenum severity, GLsizei lenght, const GLchar* message, const void* userParam)
{
	if (lenght < 0)
	{
		std::cerr << message << "\n";
	}
	else
	{
		const std::string s(message, message + lenght);
		std::cerr << s << "\n";
	}
}

/*
*	�G���g���[�|�C���g
*/
int main()
{
	// GLFW�̏�����
	if (glfwInit() != GLFW_TRUE)
	{
		return 1;
	}

	// �`��E�B���h�E�̍쐬
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
	GLFWwindow* window =
		glfwCreateWindow(1280, 720, "OpenGLGame", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return 1;
	}

	// OpenGl�R���e�L�X�g���쐬����
	glfwMakeContextCurrent(window);

	// OpenGL�֐��̃A�h���X���擾����
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		glfwTerminate();
		return 1;
	}

	glDebugMessageCallback(DebugCallback, nullptr);

	// ���C�����[�v
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// GLFW�̏I��
	glfwTerminate();

	return 0;
}