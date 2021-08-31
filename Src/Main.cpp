//4.5 �o�b�t�@�E�I�u�W�F�N�g���o�C���f�B���O�E�|�C���g�ɐݒ肷��



/*
*	@file Main.cpp
*/
#include<glad/glad.h>
#include "GLContext.h"
#include "Primitive.h"
#include <glm/gtc/matrix_transform.hpp>
#include<GLFW/glfw3.h>
#include <string>
#include <iostream>
#pragma comment(lib, "opengl32.lib")

// ���W�f�[�^
const Position positions[] =
{
	// �n��
	{-20.0f, 0.0f, 20.0f},
	{ 20.0f, 0.0f, 20.0f},
	{ 20.0f, 0.0f,-20.0f},
	{-20.0f, 0.0f,-20.0f},

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
	12,11,10,15,14,13,18,17,16,
	};

// �`��f�[�^.
const Primitive primGround(GL_TRIANGLES, 6, 0 * sizeof(GLushort), 0); // �l�p�`
const Primitive primTriangles(GL_TRIANGLES, 9, 12 * sizeof(GLushort), 0); // �O�p�`


/// ���_�V�F�[�_�[.
static const char* vsCode =
"#version 450 \n"
 "layout(location=0) in vec3 vPosition; \n"
 "layout(location=1) in vec4 vColor; \n"
 "layout(location=0) out vec4 outColor; \n"
 "out gl_PerVertex { \n"
 "  vec4 gl_Position; \n"
 "}; \n"
"layout(location=0) uniform mat4 matTRS; \n"
 "void main() { \n"
	"  outColor = vColor; \n"	
	"  gl_Position = matTRS * vec4(vPosition, 1.0); \n"
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

	// uniform�ϐ��̈ʒu.
	const GLint locMatTRS = 0;

	// ���W�ϊ��s��̉�]�p�x.
	float degree = 0;


	// ���C�����[�v
	while (!glfwWindowShouldClose(window))
	{
		glEnable(GL_DEPTH_TEST); // �[�x�o�b�t�@��L���ɂ���.
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glBindVertexArray(vao);
		glBindProgramPipeline(pipeline);


		float s = sin(glm::radians(120.0));
		float c = cos(glm::radians(120.0));
		glm::mat4 matT = glm::mat4(1);
		matT[3] = glm::vec4(-0.3, -0.5, 0.0, 1.0);
		glm::mat4 matS = glm::mat4(1);
		matS[0][0] = 0.5;
		matS[1][1] = 1.5;
		glm::mat4 matR = glm::mat4(1);
		matR[0][0] = c;
		matR[0][1] = -s;
		matR[1][0] = s;
		matR[1][1] = c;

		// �v���W�F�N�V�����s����쐬.
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		const float aspectRatio = static_cast<float>(w) / static_cast<float>(h);
		const glm::mat4 matProj =
		glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 200.0f);
		
		// �r���[�s����쐬.
		const glm::mat4 matView =
			glm::lookAt(glm::vec3(0, 20, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


		// �s����V�F�[�_�ɓ]������.
		const glm::mat4 matModel = glm::mat4(1);
		const glm::mat4 matMVP = matProj * matView * matModel;
		glProgramUniformMatrix4fv(vp, locMatTRS, 1, GL_FALSE, &matMVP[0][0]);


		primGround.Draw();
		primTriangles.Draw();

		//glBindVertexArray(0);

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