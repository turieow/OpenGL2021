//4.5 バッファ・オブジェクトをバインディング・ポイントに設定する



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

// 座標データ
const Position positions[] =
{
	// 地面
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

	{ 0.0f, 0.0f, 1.0f, 1.0f }, // 青
	{ 0.0f, 1.0f, 0.0f, 1.0f }, // 緑
	{ 1.0f, 0.0f, 0.0f, 1.0f }, // 赤
};

// インデックスデータ.
	const GLushort indices[] = {
	0, 1, 2, 2, 3, 0,
	4, 5, 6, 7, 8, 9,
	12,11,10,15,14,13,18,17,16,
	};

// 描画データ.
const Primitive primGround(GL_TRIANGLES, 6, 0 * sizeof(GLushort), 0); // 四角形
const Primitive primTriangles(GL_TRIANGLES, 9, 12 * sizeof(GLushort), 0); // 三角形


/// 頂点シェーダー.
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

/// フラグメントシェーダー.
static const GLchar * fsCode =
"#version 450 \n"
 "layout(location=0) in vec4 inColor; \n"
 "out vec4 fragColor; \n"
 "void main() { \n"
 "  fragColor = inColor; \n"
 "} \n";

/* OpenGLからのメッセージを処理する
* @param source			メッセージの発信者（OpenGL、Windows、シェーダーなど）
* @param type			メッセージの種類（エラー、警告など）
* @param id				メッセージを一位に識別する値
* @param severity		メッセージの重要度（高、中、低、最低）
* @param lenght			メッセージの文字数。府数ならメッセージは０終端されている
* @param message		メッセージ本体
* @param userParam		コールバック設定時に指定したポインタ
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
*	エントリーポイント
*/
int main()
{
	// GLFWの初期化
	if (glfwInit() != GLFW_TRUE)
	{
		return 1;
	}

	// 描画ウィンドウの作成
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

	// OpenGlコンテキストを作成する
	glfwMakeContextCurrent(window);

	// OpenGL関数のアドレスを取得する
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		glfwTerminate();
		return 1;
	}

	glDebugMessageCallback(DebugCallback, nullptr);

	// VAOを作成する.
	const GLuint vboPosition = GLContext::CreateBuffer(sizeof(positions), positions);
	const GLuint vboColor = GLContext::CreateBuffer(sizeof(colors), colors);
	const GLuint ibo = GLContext::CreateBuffer(sizeof(indices), indices);
	const GLuint vao = GLContext::CreateVertexArray(vboPosition, vboColor, ibo);
	if (!vao) {
		return 1;		
	}

	// パイプライン・オブジェクトを作成する.
	 const GLuint vp = GLContext::CreateProgram(GL_VERTEX_SHADER, vsCode);
	const GLuint fp = GLContext::CreateProgram(GL_FRAGMENT_SHADER, fsCode);
	const GLuint pipeline = GLContext::CreatePipeline(vp, fp);
	if (!pipeline) {
		return 1;		
	}

	// uniform変数の位置.
	const GLint locMatTRS = 0;

	// 座標変換行列の回転角度.
	float degree = 0;


	// メインループ
	while (!glfwWindowShouldClose(window))
	{
		glEnable(GL_DEPTH_TEST); // 深度バッファを有効にする.
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

		// プロジェクション行列を作成.
		int w, h;
		glfwGetWindowSize(window, &w, &h);
		const float aspectRatio = static_cast<float>(w) / static_cast<float>(h);
		const glm::mat4 matProj =
		glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 200.0f);
		
		// ビュー行列を作成.
		const glm::mat4 matView =
			glm::lookAt(glm::vec3(0, 20, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));


		// 行列をシェーダに転送する.
		const glm::mat4 matModel = glm::mat4(1);
		const glm::mat4 matMVP = matProj * matView * matModel;
		glProgramUniformMatrix4fv(vp, locMatTRS, 1, GL_FALSE, &matMVP[0][0]);


		primGround.Draw();
		primTriangles.Draw();

		//glBindVertexArray(0);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// 後始末.
	glDeleteProgramPipelines(1, &pipeline);
	glDeleteProgram(fp);
	glDeleteProgram(vp);
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &ibo);
	glDeleteBuffers(1, &vboColor);
	glDeleteBuffers(1, &vboPosition);

	// GLFWの終了
	glfwTerminate();

	return 0;
}