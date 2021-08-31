//4.5 バッファ・オブジェクトをバインディング・ポイントに設定する



/*
*	@file Main.cpp
*/
#include<glad/glad.h>
#include "GLContext.h"
#include<GLFW/glfw3.h>
#include <string>
#include <iostream>
#pragma comment(lib, "opengl32.lib")

// 座標データ
const Position positions[] =
{
	{-0.33f, -0.5f, 0.5f },
	{ 0.33f, -0.5f, 0.5f },
	{ 0.0f,  0.5f, 0.5f },
};

const Color colors[]
{
	{ 0.0f, 0.0f, 1.0f, 1.0f }, // 青
	{ 0.0f, 1.0f, 0.0f, 1.0f }, // 緑
	{ 1.0f, 0.0f, 0.0f, 1.0f }, // 赤
};

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

	// メインループ
	while (!glfwWindowShouldClose(window))
	{
		glClearColor(0.1f, 0.3f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// GLFWの終了
	glfwTerminate();

	return 0;
}