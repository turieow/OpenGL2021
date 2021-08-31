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



/// ���W�f�[�^:�l�p�`
const glm::vec3 posRectangle[] = {
	{-0.2f, -0.5f, 0.1f},
	{ 0.3f, -0.5f, 0.1f},
	{ 0.3f,  0.3f, 0.1f},
	{ 0.3f,  0.3f, 0.1f},
	{-0.2f,  0.3f, 0.1f},
	{-0.2f, -0.5f, 0.1f},
};

/// ���W�f�[�^:�O�p�`
const glm::vec3 posTriangle[] = {
   {(-0.33f / 2.0f) * 10.0f,(0.5f / 2.0f) * 10.0f, 0.6f },
   {(0.33f / 2.0f) * 10.0f,(0.5f / 2.0f) * 10.0f, 0.6f },
   {(0.33f / 2.0f + 0.165f) * 10.0f,(0.5f / 2.0f + 0.5f) * 10.0f, 0.6f },
   {(0.00f / 2.0f + 0.165f) * 10.0f,(-0.5f / 2.0f + 0.5f) * 10.0f, 0.6f },
};

const glm::vec3 posCube[] = {
	{ 0, 0, 0}, { 1, 0, 0}, { 1, 0, 1}, { 0, 0, 1},
	{ 0, 1, 0}, { 1, 1, 0}, { 1, 1, 1}, { 0, 1, 1},
};

const glm::vec3 posTree[] = {
	// ��(�t)
	{ 0.0f, 3.0f, 0.0f}, // 0
	{ 0.0f, 1.0f,-1.0f}, // 1
	{-1.0f, 1.0f, 0.0f}, // 2
	{ 0.0f, 1.0f, 1.0f}, // 3
	{ 1.0f, 1.0f, 0.0f}, // 4
	{ 0.0f, 1.0f,-1.0f}, // 5
};

const glm::vec3 posWarehouse[] = {
	{ 0.0f, 3.0f, 0.0f}, // 0
	{ 0.0f, 1.0f,-1.0f}, // 1
	{-1.0f, 1.0f, 0.0f}, // 2
	{ 0.0f, 1.0f, 1.0f}, // 3
	{ 1.0f, 1.0f, 0.0f}, // 4
	{ 0.0f, 1.0f,-1.0f}, // 5
};

const glm::vec4 colGround[] ={
	{0.0f, 1.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
};

const glm::vec4 colRectangle[] = {
	{1.0f, 0.0f, 0.0f, 1.0f},
	{1.0f, 1.0f, 0.0f, 1.0f},
	{1.0f, 0.0f, 0.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
	{0.0f, 1.0f, 1.0f, 1.0f},
	{0.0f, 0.0f, 1.0f, 1.0f},
};

const glm::vec4 colTriangle[] = {
	{ 0.0f, 0.0f, 1.0f, 1.0f }, // ��
	{ 0.0f, 1.0f, 0.0f, 1.0f }, // ��
	{ 1.0f, 0.0f, 0.0f, 1.0f }, // ��
};

	// ������
const glm::vec2 tcRectangle[] = {
	{ 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f},
	{ 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f},
};
	
	  // ��(�t)
const glm::vec2 tcTree[] = {
	{ 0.5f, 1.0f},
	{ 0.0f, 0.5f},
	{ 0.25f, 0.5f},
	{ 0.5f, 0.5f},
	{ 0.75f, 0.5f},
	{ 1.0f, 0.5f},
};

// �C���f�b�N�X�f�[�^.

/// �C���f�b�N�X�f�[�^:�l�p�`
const GLushort indexRectangle[] = {
	0, 1, 2, 3, 4, 5,
};

/// �C���f�b�N�X�f�[�^:�O�p�`
const GLushort indexTriangle[] = {
	12,11,10,15,14,13,18,17,16,
};

	// ������
/// �C���f�b�N�X�f�[�^:������
const GLushort indexCube[] = {
	 0, 1, 2, 2, 3, 0, 4, 5, 1, 1, 0, 4,
	 5, 6, 2, 2, 1, 5, 6, 7, 3, 3, 2, 6,
	7, 4, 0, 0, 3, 7, 7, 6, 5, 5, 4, 7,
};
	
	 // ��
/// �C���f�b�N�X�f�[�^:��
const GLushort indexTree[] = {
	0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 1, 4, 3, 3, 2, 1, // �t
};

/// �C���f�b�N�X�f�[�^:����
const GLushort indexWarehouse[] = {
  0, 1, 6, 6, 5, 0,
  1, 2, 7, 7, 6, 1,
};

// �摜�f�[�^.
const int imageGroundWidth = 8; // �摜�̕�.
const int imageGroundHeight = 8; // �摜�̍���.
const GLuint X = 0xff'18'18'18; // ��.
const GLuint W = 0xff'ff'ff'ff; // ��.
const GLuint R = 0xff'10'10'e0; // ��.
const GLuint B = 0xff'e0'10'10; // ��.
const GLuint imageGround[imageGroundWidth * imageGroundHeight] = {
X, B, B, B, X, W, W, W,
X, B, B, B, X, W, W, W,
X, B, B, B, X, W, W, W,
X, X, X, X, X, X, X, X,
W, W, X, R, R, R, X, W,
W, W, X, R, R, R, X, W,
W, W, X, R, R, R, X, W,
X, X, X, X, X, X, X, X,
};

/// ���_�V�F�[�_�[.
static const char* vsCode =
"#version 450 \n"
 "layout(location=0) in vec3 vPosition; \n"
 "layout(location=1) in vec4 vColor; \n"
"layout(location=2) in vec2 vTexcoord; \n"
 "layout(location=0) out vec4 outColor; \n"
"layout(location=1) out vec2 outTexcoord; \n"
 "out gl_PerVertex { \n"
 "  vec4 gl_Position; \n"
 "}; \n"
"layout(location=0) uniform mat4 matTRS; \n"
 "void main() { \n"
	"  outColor = vColor; \n"	
	"  outTexcoord = vTexcoord; \n"
	"  gl_Position = matTRS * vec4(vPosition, 1.0); \n"
 "} \n";

/// �t���O�����g�V�F�[�_�[.
static const GLchar* const fsCode =
"#version 450 \n"
"layout(location=0) in vec4 inColor; \n"
"layout(location=1) in vec2 inTexcoord; \n"
"out vec4 fragColor; \n"
"layout(binding=0) uniform sampler2D texColor; \n"
"void main() { \n"
"  vec4 tc = texture(texColor, inTexcoord); \n"
"  fragColor = inColor * tc; \n"
"} \n";

/// �}�b�v�f�[�^.
int mapData[10][10] = {
{ 0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
{ 0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
{ 0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
{ 0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
{ 0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
{ 0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
{ 0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
{ 0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
{ 0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
{ 0, 0, 0, 1, 2, 2, 1, 0, 0, 0},
};

// �؂�A����ʒu��\���񎟌��z��
int objectMapData[10][10] =
{
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
	{ 1, 1, 1, 0, 0, 0, 0, 1, 1, 1},
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

	PrimitiveBuffer primitiveBuffer(100'000, 300'000);

	// VAO���쐬����.
	primitiveBuffer.AddFromObjFile("Res/Ground.obj");
	primitiveBuffer.AddFromObjFile("Res/Rectangle.obj");
	primitiveBuffer.AddFromObjFile("Res/Cube.obj");
	primitiveBuffer.AddFromObjFile("Res/Tree.obj");
	primitiveBuffer.AddFromObjFile("Res/Warehouse.obj");

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

	// �e�N�X�`�����쐬.
	const GLuint texGround = GLContext::CreateImage2D("Res/T_Ground.tga");
	const GLuint texTriangle = GLContext::CreateImage2D("Res/T_Triangle.tga");
	const GLuint texGreen = GLContext::CreateImage2D(8, 8, imageGround,
		GL_RGBA, GL_UNSIGNED_BYTE);
	const GLuint texRoad = GLContext::CreateImage2D(8, 8, imageGround,
		GL_RGBA, GL_UNSIGNED_BYTE);
	const GLuint texTree = GLContext::CreateImage2D(8, 8, imageGround,
		GL_RGBA, GL_UNSIGNED_BYTE);
	const GLuint texWarehouse = GLContext::CreateImage2D(8, 8, imageGround,
		GL_RGBA, GL_UNSIGNED_BYTE);

	if (!texGround || !texTriangle) {
		return 1;
	}

	// �T���v�����쐬.
	 const GLuint sampler = GLContext::CreateSampler(GL_CLAMP_TO_EDGE);
	if (!sampler) {
		return 1;		
	}

	// ���C�����[�v
	while (!glfwWindowShouldClose(window))
	{
		glEnable(GL_DEPTH_TEST); // �[�x�o�b�t�@��L���ɂ���.
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		primitiveBuffer.BindVertexArray();
		glBindProgramPipeline(pipeline);
		glBindSampler(0, sampler);

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

		glBindTextureUnit(0, texGround); // �e�N�X�`�������蓖�Ă�.


		primGround.Draw();

		glBindTextureUnit(0, texTriangle); // �e�N�X�`�������蓖�Ă�.
		primTriangles.Draw();
		primCube.Draw();

		// �}�b�v�ɔz�u���镨�̂̕\���f�[�^.
		struct ObjectData {
			Primitive prim; // �\������v���~�e�B�u.
			GLuint tex;     // �v���~�e�B�u�ɓ\��e�N�X�`��.			
		};

		// �`�悷�镨�̂̃��X�g.
		const ObjectData objectList[] = {
		{ Primitive(), 0 },    // �Ȃ�.
		{ primTree, texTree }, // ��.
		{ primWarehouse, texWarehouse }, // ����
		};

		// �؂�A����.
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				    // �`�悷�镨�̂̔ԍ����擾.
				const int objectNo = objectMapData[y][x];
				if (objectNo <= 0 || objectNo >= std::size(objectList)) {
					continue;					
				}
				const ObjectData p = objectList[objectNo];
				
				        // �l�p�`��4x4m�Ȃ̂ŁAx��y��4�{�����ʒu�ɕ\������.
				const glm::vec3 position(x * 4 - 20, 0, y * 4 - 20);
				
				        // �s����V�F�[�_�ɓ]������ 
				const glm::mat4 matModel = glm::translate(glm::mat4(1), position);
				const glm::mat4 matMVP = matProj * matView * matModel;
				glProgramUniformMatrix4fv(vp, locMatTRS, 1, GL_FALSE, &matMVP[0][0]);
				
				glBindTextureUnit(0, p.tex); // �e�N�X�`�������蓖�Ă�.
				p.prim.Draw();
			}
		}

		// �}�b�v��(-20,-20)-(20,20)�͈̔͂ɕ`��.
		const GLuint mapTexList[] = { texGreen, texGround, texRoad };
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				    // �l�p�`��4x4m�Ȃ̂ŁAx��y��4�{�����ʒu�ɕ\������.
				const glm::vec3 position(x * 4 - 20, 0, y * 4 - 20);
				
				        // �s����V�F�[�_�ɓ]������ 
				const glm::mat4 matModel = glm::translate(glm::mat4(1), position);
				const glm::mat4 matMVP = matProj * matView * matModel;
				glProgramUniformMatrix4fv(vp, locMatTRS, 1, GL_FALSE, &matMVP[0][0]);
				
				const int textureNo = mapData[y][x];
				glBindTextureUnit(0, mapTexList[textureNo]); // �e�N�X�`�������蓖�Ă�.
				primitiveBuffer.Get(0).Draw();
			}			
		}

		// �e�N�X�`���̊��蓖�Ă�����.
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindSampler(0, 0);
		glBindProgramPipeline(0);
		primitiveBuffer.UnbindVertexArray();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// ��n��.
	glDeleteSamplers(1, &sampler);
	glDeleteTextures(1, &texGround);
	glDeleteProgramPipelines(1, &pipeline);
	glDeleteProgram(fp);
	glDeleteProgram(vp);

	// GLFW�̏I��
	glfwTerminate();

	return 0;
}