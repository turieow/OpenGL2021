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
	{-0.3f, -0.3f, 0.4f},
	{ 0.2f, -0.3f, 0.4f},
	{ 0.2f,  0.5f, 0.4f},
	{-0.3f,  0.5f, 0.4f},

	{-0.2f, -0.5f, 0.1f},
	{ 0.3f, -0.5f, 0.1f},
	{ 0.3f,  0.3f, 0.1f},
	{ 0.3f,  0.3f, 0.1f},
	{-0.2f,  0.3f, 0.1f},
	{-0.2f, -0.5f, 0.1f},

	{-0.33f, -0.5f, 0.5f },
	{ 0.33f, -0.5f, 0.5f },
	{ 0.0f,  0.5f, 0.5f },
};

const Color colors[]
{
	{0.0f, 1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},

	{1.0f, 0.0f, 0.0f, 1.0f},
	{1.0f, 1.0f, 0.0f, 1.0f},
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{0.0f, 1.0f, 1.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},

	{ 0.0f, 0.0f, 1.0f, 1.0f }, // ��
	{ 0.0f, 1.0f, 0.0f, 1.0f }, // ��
	{ 1.0f, 0.0f, 0.0f, 1.0f }, // ��
};

// �C���f�b�N�X�f�[�^.
	const GLushort indices[] = {
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 7, 8, 9,
	};

/// ���_�V�F�[�_�[.
static const char* vsCode =
"#version 450 \n"
 "layout(location=0) in vec3 vPosition; \n"
 "layout(location=1) in vec4 vColor; \n"
 "layout(location=0) out vec4 outColor; \n"
 "out gl_PerVertex { \n"
 "  vec4 gl_Position; \n"
 "}; \n"
 "void main() { \n"
 "  outColor = vColor; \n"
	"  float s = sin(1.0); \n"
	 "  float c = cos(1.0); \n"
	 "  vec3 p = vPosition; \n"
	 "  p.x = vPosition.x * c - vPosition.y * s; \n"
	 "  p.y = vPosition.x * s + vPosition.y * c; \n"
	"  gl_Position.xyz = p * vec3(0.5, 1.5, 1.0) + vec3(-0.3,-0.5, 0.0); \n"
 "  gl_Position.w = 1.0; \n"
 "} \n";

/// �t���O�����g�V�F�[�_�[.
static const GLchar * fsCode =
"#version 450 \n"
 "layout(location=0) in vec4 inColor; \n"
 "out vec4 fragColor; \n"
 "void main() { \n"
 "  fragColor = inColor; \n"
 "} \n";

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

	// VAO���쐬����.
	const GLuint vboPosition = GLContext::CreateBuffer(sizeof(positions), positions);
	const GLuint vboColor = GLContext::CreateBuffer(sizeof(colors), colors);
	const GLuint ibo = GLContext::CreateBuffer(sizeof(indices), indices);
	const GLuint vao = GLContext::CreateVertexArray(vboPosition, vboColor, ibo);
	if (!vao) {
		return 1;		
	}

	// �p�C�v���C���E�I�u�W�F�N�g���쐬����.
	 const GLuint vp = GLContext::CreateProgram(GL_VERTEX_SHADER, vsCode);
	const GLuint fp = GLContext::CreateProgram(GL_FRAGMENT_SHADER, fsCode);
	const GLuint pipeline = GLContext::CreatePipeline(vp, fp);
	if (!pipeline) {
		return 1;		
	}

	// ���C�����[�v
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);
		glBindProgramPipeline(pipeline);
		
		glDrawElements(
			GL_TRIANGLES, sizeof(indices) / sizeof(indices[0]), GL_UNSIGNED_SHORT, 0);
		glBindProgramPipeline(0);
		glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// ��n��.
	glDeleteProgramPipelines(1, &pipeline);
	glDeleteProgram(fp);
	glDeleteProgram(vp);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vboColor);
	glDeleteBuffers(1, &vboPosition);

	// GLFW�̏I��
	glfwTerminate();

	return 0;
}