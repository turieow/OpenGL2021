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



/// 座標データ:四角形
const glm::vec3 posRectangle[] = {
	{-0.2f, -0.5f, 0.1f},
	{ 0.3f, -0.5f, 0.1f},
	{ 0.3f,  0.3f, 0.1f},
	{ 0.3f,  0.3f, 0.1f},
	{-0.2f,  0.3f, 0.1f},
	{-0.2f, -0.5f, 0.1f},
};

/// 座標データ:三角形
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
	// 木(葉)
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
	{ 0.0f, 0.0f, 1.0f, 1.0f }, // 青
	{ 0.0f, 1.0f, 0.0f, 1.0f }, // 緑
	{ 1.0f, 0.0f, 0.0f, 1.0f }, // 赤
};

	// 立方体
const glm::vec2 tcRectangle[] = {
	{ 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f},
	{ 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f},
};
	
	  // 木(葉)
const glm::vec2 tcTree[] = {
	{ 0.5f, 1.0f},
	{ 0.0f, 0.5f},
	{ 0.25f, 0.5f},
	{ 0.5f, 0.5f},
	{ 0.75f, 0.5f},
	{ 1.0f, 0.5f},
};

// インデックスデータ.

/// インデックスデータ:四角形
const GLushort indexRectangle[] = {
	0, 1, 2, 3, 4, 5,
};

/// インデックスデータ:三角形
const GLushort indexTriangle[] = {
	12,11,10,15,14,13,18,17,16,
};

	// 立方体
/// インデックスデータ:立方体
const GLushort indexCube[] = {
	 0, 1, 2, 2, 3, 0, 4, 5, 1, 1, 0, 4,
	 5, 6, 2, 2, 1, 5, 6, 7, 3, 3, 2, 6,
	7, 4, 0, 0, 3, 7, 7, 6, 5, 5, 4, 7,
};
	
	 // 木
/// インデックスデータ:木
const GLushort indexTree[] = {
	0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 1, 4, 3, 3, 2, 1, // 葉
};

/// インデックスデータ:建物
const GLushort indexWarehouse[] = {
  0, 1, 6, 6, 5, 0,
  1, 2, 7, 7, 6, 1,
};

// 画像データ.
const int imageGroundWidth = 8; // 画像の幅.
const int imageGroundHeight = 8; // 画像の高さ.
const GLuint X = 0xff'18'18'18; // 黒.
const GLuint W = 0xff'ff'ff'ff; // 白.
const GLuint R = 0xff'10'10'e0; // 赤.
const GLuint B = 0xff'e0'10'10; // 青.
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

/// 頂点シェーダー.
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

/// フラグメントシェーダー.
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

/// マップデータ.
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

// 木を植える位置を表す二次元配列
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

	PrimitiveBuffer primitiveBuffer(100'000, 300'000);

	// VAOを作成する.
	primitiveBuffer.AddFromObjFile("Res/Ground.obj");
	primitiveBuffer.AddFromObjFile("Res/Rectangle.obj");
	primitiveBuffer.AddFromObjFile("Res/Cube.obj");
	primitiveBuffer.AddFromObjFile("Res/Tree.obj");
	primitiveBuffer.AddFromObjFile("Res/Warehouse.obj");

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

	// テクスチャを作成.
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

	// サンプラを作成.
	 const GLuint sampler = GLContext::CreateSampler(GL_CLAMP_TO_EDGE);
	if (!sampler) {
		return 1;		
	}

	// メインループ
	while (!glfwWindowShouldClose(window))
	{
		glEnable(GL_DEPTH_TEST); // 深度バッファを有効にする.
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

		glBindTextureUnit(0, texGround); // テクスチャを割り当てる.


		primGround.Draw();

		glBindTextureUnit(0, texTriangle); // テクスチャを割り当てる.
		primTriangles.Draw();
		primCube.Draw();

		// マップに配置する物体の表示データ.
		struct ObjectData {
			Primitive prim; // 表示するプリミティブ.
			GLuint tex;     // プリミティブに貼るテクスチャ.			
		};

		// 描画する物体のリスト.
		const ObjectData objectList[] = {
		{ Primitive(), 0 },    // なし.
		{ primTree, texTree }, // 木.
		{ primWarehouse, texWarehouse }, // 建物
		};

		// 木を植える.
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				    // 描画する物体の番号を取得.
				const int objectNo = objectMapData[y][x];
				if (objectNo <= 0 || objectNo >= std::size(objectList)) {
					continue;					
				}
				const ObjectData p = objectList[objectNo];
				
				        // 四角形が4x4mなので、xとyを4倍した位置に表示する.
				const glm::vec3 position(x * 4 - 20, 0, y * 4 - 20);
				
				        // 行列をシェーダに転送する 
				const glm::mat4 matModel = glm::translate(glm::mat4(1), position);
				const glm::mat4 matMVP = matProj * matView * matModel;
				glProgramUniformMatrix4fv(vp, locMatTRS, 1, GL_FALSE, &matMVP[0][0]);
				
				glBindTextureUnit(0, p.tex); // テクスチャを割り当てる.
				p.prim.Draw();
			}
		}

		// マップを(-20,-20)-(20,20)の範囲に描画.
		const GLuint mapTexList[] = { texGreen, texGround, texRoad };
		for (int y = 0; y < 10; ++y) {
			for (int x = 0; x < 10; ++x) {
				    // 四角形が4x4mなので、xとyを4倍した位置に表示する.
				const glm::vec3 position(x * 4 - 20, 0, y * 4 - 20);
				
				        // 行列をシェーダに転送する 
				const glm::mat4 matModel = glm::translate(glm::mat4(1), position);
				const glm::mat4 matMVP = matProj * matView * matModel;
				glProgramUniformMatrix4fv(vp, locMatTRS, 1, GL_FALSE, &matMVP[0][0]);
				
				const int textureNo = mapData[y][x];
				glBindTextureUnit(0, mapTexList[textureNo]); // テクスチャを割り当てる.
				primitiveBuffer.Get(0).Draw();
			}			
		}

		// テクスチャの割り当てを解除.
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, 0);

		glBindSampler(0, 0);
		glBindProgramPipeline(0);
		primitiveBuffer.UnbindVertexArray();

		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// 後始末.
	glDeleteSamplers(1, &sampler);
	glDeleteTextures(1, &texGround);
	glDeleteProgramPipelines(1, &pipeline);
	glDeleteProgram(fp);
	glDeleteProgram(vp);

	// GLFWの終了
	glfwTerminate();

	return 0;
}