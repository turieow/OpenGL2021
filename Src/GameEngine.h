#pragma once
/**
* @file GameEngine.h
*/
#ifndef GAMEENGINE_H_INCLUDED
#define GAMEENGINE_H_INCLUDED
#include "Primitive.h"
#include "Texture.h"
#include "ProgramPipeline.h"
#include "Sampler.h"
#include "Actor.h"
#include "Camera.h"
#include <GLFW/glfw3.h>
#include <unordered_map>
#include <random>

using ActorList = std::vector<std::shared_ptr<Actor>>;
using TextureBuffer = std::unordered_map<std::string, std::shared_ptr<Texture>>;

/**
* ゲームエンジン
*/
class GameEngine
{
public:
    static bool Initialize();
    static void Finalize();
    static GameEngine& Get();

    ActorList& GetActors(Layer layer = Layer::Default)
    {
        return actors[static_cast<int>(layer)];
    }
    void AddActor(std::shared_ptr<Actor> actor) { newActors.push_back(actor); }
    void UpdateActors(float deltaTime);
    void PostUpdateActors();
    void UpdatePhysics(float deltaTime);
    void UpdateCamera();
    void NewFrame();
    void RemoveDeadActors();
    void RenderDefault();
    void RenderUI();
    void PostRender();

    PrimitiveBuffer& GetPrimitiveBuffer() { return *primitiveBuffer; }
    bool LoadPrimitive(const char* filename);
    const Primitive& GetPrimitive(const char* filename) const;
    const Primitive& GetPrimitive(int n) const { return primitiveBuffer->Get(n); }

    std::shared_ptr<Texture> LoadTexture(const char* filename);

    /**
    * この関数がtrueを返したらウィンドウを閉じる(=アプリを終了させる)
    */
    bool WindowShouldClose() const
    {
        return glfwWindowShouldClose(window);
    }

    /**
    * キーが押されていたらtrue、押されていなかったらfalse
    */
    bool GetKey(int key) const
    {
        return glfwGetKey(window, key) == GLFW_PRESS;
    }

    /**
    * ボタンが押されていたらtrue、押されていなかったらfalse
    */
    int GetMouseButton(int button) const
    {
        return glfwGetMouseButton(window, button);
    }

    /**
    * ウィンドウサイズを返す
    */
    glm::vec2 GetWindowSize() const
    {
        return windowSize;
    }

    /**
    * フロントバッファとバックバッファを交換する
    */
    void SwapBuffers() const
    {
        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    /**
    * アプリ起動時からの経過時間(秒)を取得する
    */
    double GetTime() const
    {
        return glfwGetTime();
    }

    // メインカメラを取得する
    Camera& GetCamera() { return mainCamera; }
    const Camera& GetCamera() const { return mainCamera; }

    // テキストで作成していないメンバ関数
    std::shared_ptr<Texture> GetTexture(const char* filename) const;
    std::shared_ptr<Actor> FindActor(const char* name);
    unsigned int GetRandom();

private:
    GameEngine() = default;
    ~GameEngine() = default;
    GameEngine(const GameEngine&) = delete;
    GameEngine& operator=(const GameEngine&) = delete;

    GLFWwindow* window = nullptr;
    glm::vec2 windowSize = glm::vec2(0);
    std::shared_ptr<ProgramPipeline> pipeline;
    std::shared_ptr<ProgramPipeline> pipelineUI;
    std::shared_ptr<Sampler> sampler;
    std::shared_ptr<Sampler> samplerUI;
    ActorList actors[layerCount]; // アクター配列
    ActorList newActors; // 追加するアクターの配列
    std::shared_ptr<PrimitiveBuffer> primitiveBuffer; // プリミティブ配列
    TextureBuffer textureBuffer;                      // テクスチャ配列
    Camera mainCamera;  // メインカメラ

    // テキストで作成していないメンバ変数
    std::mt19937 rg;
};

#endif // GAMEENGINE_H_INCLUDED