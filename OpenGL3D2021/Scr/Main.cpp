/* 
*	@file Main.cpp
*/
#include<GLFW/glfw3.h>
#pragma comment(lib, "opengl32.lib")

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
	using pfnglClear = void (GLAPIENTRY*)(GLbitfield);
	pfnglClear glClear =
		reinterpret_cast<pfnglClear> (glfwGetProcAddress("glClear"));
	using pfnglClearColor =
		void (GLAPIENTRY*)(GLfloat, GLfloat, GLfloat, GLfloat);
	pfnglClearColor glClearColor =
		reinterpret_cast<pfnglClearColor>(glfwGetProcAddress("glClearColor"));

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