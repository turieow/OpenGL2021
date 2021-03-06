#pragma once
/**
* @file Texture.h
*/
#ifndef TEXTURE_H_INCLUDED
#define TEXTURE_H_INCLUDED
#include <glad/glad.h>
#include "GLContext.h"
#include <string>

/**
* テクスチャを管理するクラス.
*/
class Texture
{
public:
	Texture(const char* filename);
	~Texture();

	// オブジェクトの有効性を判定する
	bool IsValid() const;

	// バインド管理
	void Bind(GLuint unit) const;
	void Unbind(GLuint unit) const;

private:
	std::string name; // 画像ファイル名.
	GLuint id = 0;    // オブジェクトID.
};

#endif // TEXTURE_H_INCLUDED