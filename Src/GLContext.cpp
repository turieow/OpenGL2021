/*
*	@file GLContext.cpp
*/
#include "GLContext.h"
#include <glm/glm.hpp>
#include <vector>
#include <iostream>

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
	GLuint CreateVertexArray(GLuint vboPosition, GLuint vboColor,
		GLuint vboTexcoord, GLuint ibo)
	{
		if (!vboPosition || !vboColor || !vboTexcoord || !ibo) {
			std::cerr << "[エラー]" << __func__ << ":バッファオブジェクトが0です。\n";
			return 0;			
		}

		GLuint id = 0;
		glCreateVertexArrays(1, &id);

		const GLuint positionIndex = 0;
		const GLuint positionBindingIndex = 0;
		glEnableVertexArrayAttrib(id, positionIndex);
		glVertexArrayAttribFormat(id, positionIndex, 3, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(id, positionIndex, positionBindingIndex);
		glVertexArrayVertexBuffer(
			id, positionBindingIndex, vboPosition, 0, sizeof(Position));

		const GLuint colorIndex = 1;
		const GLuint colorBindingIndex = 1;
		glEnableVertexArrayAttrib(id, colorIndex);
		glVertexArrayAttribFormat(id, colorIndex, 4, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(id, colorIndex, colorBindingIndex);
		glVertexArrayVertexBuffer(id, colorBindingIndex, vboColor, 0, sizeof(Color));

		// テクスチャ座標データをバインディングポイントに割り当てる.
		const GLuint texcoordIndex = 2;
		const GLuint texcoordBindingIndex = 2;
		glEnableVertexArrayAttrib(id, texcoordIndex);
		glVertexArrayAttribFormat(id, texcoordIndex, 2, GL_FLOAT, GL_FALSE, 0);
		glVertexArrayAttribBinding(id, texcoordIndex, texcoordBindingIndex);
		glVertexArrayVertexBuffer(
			id, texcoordBindingIndex, vboTexcoord, 0, sizeof(glm::vec2));
		
		glVertexArrayElementBuffer(id, ibo);

		return id;
	}

	/**
	* シェーダー・プログラムをビルドする.
	*
	* @param type シェーダーの種類.
	* @param code シェーダー・プログラムへのポインタ.
	*
	* @retval 0より大きい 作成したプログラム・オブジェクト.
	* @retval 0          プログラム・オブジェクトの作成に失敗.
	*/
	GLuint CreateProgram(GLenum type, const GLchar* code)
	{
		GLuint program = glCreateShaderProgramv(type, 1, &code);

		GLint status = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			GLint infoLen = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen) {
				std::vector<char> buf;
				buf.resize(infoLen);
				if ((int)buf.size() >= infoLen) {
					glGetProgramInfoLog(program, infoLen, nullptr, buf.data());
					std::cerr << "[エラー]" << __func__ <<
						":シェーダーのビルドに失敗.\n" << buf.data() << "\n";
				}
			}
			glDeleteProgram(program);
			return 0;
		}
		return program;
	}

	/**
	* パイプライン・オブジェクトを作成する.
	*
	* @param vp  頂点シェーダー・プログラム.
	* @param fp  フラグメントシェーダー・プログラム.
	*
	* @retval 0より大きい 作成したパイプライン・オブジェクト.
	* @retval 0         パイプライン・オブジェクトの作成に失敗.
	*/
	GLuint CreatePipeline(GLuint vp, GLuint fp)
	{
		glGetError(); // エラー状態をリセット.

		GLuint id;
		glCreateProgramPipelines(1, &id);
		glUseProgramStages(id, GL_VERTEX_SHADER_BIT, vp);
		glUseProgramStages(id, GL_FRAGMENT_SHADER_BIT, fp);

		if (glGetError() != GL_NO_ERROR) {
			std::cerr << "[エラー]" << __func__ << ":プログラムパイプラインの作成に失敗.\n";
			glDeleteProgramPipelines(1, &id);
			return 0;			
		}

		GLint testVp = 0;
		glGetProgramPipelineiv(id, GL_VERTEX_SHADER, &testVp);
		if (testVp != vp) {
			std::cerr << "[エラー]" << __func__ << ":頂点シェーダの設定に失敗.\n";
			glDeleteProgramPipelines(1, &id);
			return 0;
			
		}
		 GLint testFp = 0;
		glGetProgramPipelineiv(id, GL_FRAGMENT_SHADER, &testFp);
		if (testFp != fp) {
			std::cerr << "[エラー]" << __func__ << ":フラグメントシェーダの設定に失敗.\n";
			glDeleteProgramPipelines(1, &id);
			return 0;			
		}

		return id;
	}

	/**
	* サンプラ・オブジェクトを作成する.
	*
	* @param wrapMode  ラップ・モード.
	*
	* @retval 0以外 作成したサンプラ・オブジェクト.
	* @retval 0     サンプラ・オブジェクトの作成に失敗.
	*/
	GLuint CreateSampler(GLenum wrapMode)
	{
		glGetError(); // エラー状態をリセット.

		// サンプラ・オブジェクトを作成する.
		GLuint id;
		glCreateSamplers(1, &id);
		if (glGetError() != GL_NO_ERROR) {
			std::cerr << "[エラー]" << __func__ << "サンプラの作成に失敗\n";
			glDeleteSamplers(1, &id);
			return 0;			
		}

		// ラップ・モードを設定する.
		 glSamplerParameteri(id, GL_TEXTURE_WRAP_S, wrapMode);
		glSamplerParameteri(id, GL_TEXTURE_WRAP_T, wrapMode);
		if (glGetError() != GL_NO_ERROR) {
			std::cerr << "[エラー]" << __func__ << ":ラップモードではない値が指定された.\n";
			glDeleteSamplers(1, &id);
			return 0;			
		}

		// フィルタを設定する.
		 glSamplerParameteri(id, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
		glSamplerParameteri(id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		if (glGetError() != GL_NO_ERROR) {
			std::cerr << "[エラー]" << __func__ << ":フィルタではない値が指定された.\n";
			glDeleteSamplers(1, &id);
			return 0;			
		}

		return id;
	}

	/**
* 2Dテクスチャを作成する.
*
* @param width   画像の幅(ピクセル数).
* @param height  画像の高さ(ピクセル数).
* @param data    画像データのアドレス.
*
* @retval 0以外  作成したテクスチャ・オブジェクトのID.
* @retval 0      テクスチャの作成に失敗.
*/
	GLuint CreateImage2D(GLsizei width, GLsizei height, const void* data)
	{
		glGetError(); // エラー状態をリセット.

		// テクスチャ・オブジェクトを作成し、GPUメモリを確保する.
		GLuint id;
		glCreateTextures(GL_TEXTURE_2D, 1, &id);
		glTextureStorage2D(id, 1, GL_RGBA8, width, height);

		// GPUメモリにデータを転送する.
		glTextureSubImage2D(id, 0, 0, 0, width, height, GL_RGBA, GL_UNSIGNED_BYTE, data);
		const GLenum result = glGetError();
		if (result != GL_NO_ERROR) {
			std::cerr << "[エラー]" << __func__ << "テクスチャの作成に失敗\n";
			glDeleteTextures(1, &id);
			return 0;
		}

		return id;
	}
} // namespace GLContext