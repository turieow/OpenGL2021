/**
* @file Main.cpp
*/
#include <glad/glad.h>
#include "GLContext.h"
#include "GameEngine.h"
#include "Primitive.h"
#include "ProgramPipeline.h"
#include "Texture.h"
#include "Sampler.h"
#include "Actor.h"
#include "GameEngine.h"
#include "GameManager.h"
#include "Actor/PlayerActor.h"
#include "Actor/T34TankActor.h"
#include "Actor/RandomMovingEnemyActor.h"
#include "Actor/ElevatorActor.h"
#include <glm/gtc/matrix_transform.hpp>
#include <string>
#include <iostream>
#include <memory>
#include <algorithm>
#include <unordered_map>
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
    {(-0.33f / 2.0f) * 10.0f, (0.5f / 2.0f) * 10.0f, 0.6f },
    {(0.33f / 2.0f) * 10.0f, (0.5f / 2.0f) * 10.0f, 0.6f },
    {(0.00f / 2.0f) * 10.0f, (-0.5f / 2.0f) * 10.0f, 0.6f },
    {(-0.33f / 2.0f - 0.165f) * 10.0f, (0.5f / 2.0f + 0.5f) * 10.0f, 0.6f },
    {(0.33f / 2.0f - 0.165f) * 10.0f, (0.5f / 2.0f + 0.5f) * 10.0f, 0.6f },
    {(0.00f / 2.0f - 0.165f) * 10.0f, (-0.5f / 2.0f + 0.5f) * 10.0f, 0.6f },
    {(-0.33f / 2.0f + 0.165f) * 10.0f, (0.5f / 2.0f + 0.5f) * 10.0f, 0.6f },
    {(0.33f / 2.0f + 0.165f) * 10.0f, (0.5f / 2.0f + 0.5f) * 10.0f, 0.6f },
    {(0.00f / 2.0f + 0.165f) * 10.0f, (-0.5f / 2.0f + 0.5f) * 10.0f, 0.6f },
};

/// 座標データ:立方体
const glm::vec3 posCube[] = {
    { 0, 0, 0}, { 1, 0, 0}, { 1, 0, 1}, { 0, 0, 1},
    { 0, 1, 0}, { 1, 1, 0}, { 1, 1, 1}, { 0, 1, 1},
};

/// 座標データ:
const glm::vec3 posTree[] = {
    // 木(葉)
    { 0.0f, 3.0f, 0.0f},
    { 0.0f, 1.0f,-1.0f},
    {-1.0f, 1.0f, 0.0f},
    { 0.0f, 1.0f, 1.0f},
    { 1.0f, 1.0f, 0.0f},
    { 0.0f, 1.0f,-1.0f},

    // 木(幹)
    { 0.0f, 2.0f, 0.0f},
    { 0.0f, 0.0f,-0.5f},
    {-0.5f, 0.0f, 0.0f},
    { 0.0f, 0.0f, 0.5f},
    { 0.5f, 0.0f, 0.0f},
    { 0.0f, 0.0f,-0.5f},
};

/// 座標データ:建物
const glm::vec3 posWarehouse[] = {
    {-2, 0,-2}, {-2, 0, 2}, { 2, 0, 2}, { 2, 0,-2}, {-2, 0,-2},
    {-2, 2,-2}, {-2, 2, 2}, { 2, 2, 2}, { 2, 2,-2}, {-2, 2,-2},
    { 2, 2, 2}, { 2, 2,-2},
};

/// 色データ:地面
const glm::vec4 colGround[] = {
    {1.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
    {1.0f, 1.0f, 1.0f, 1.0f},
};

/// 色データ:四角形
const glm::vec4 colRectangle[] = {
    {1.0f, 0.0f, 0.0f, 1.0f},
    {1.0f, 1.0f, 0.0f, 1.0f},
    {1.0f, 0.0f, 0.0f, 1.0f},
    {0.0f, 0.0f, 1.0f, 1.0f},
    {0.0f, 1.0f, 1.0f, 1.0f},
    {0.0f, 0.0f, 1.0f, 1.0f},
};

/// 色データ:三角形
const glm::vec4 colTriangle[] = {
    { 0.0f, 1.0f, 1.0f, 1.0f }, // 水色
    { 1.0f, 1.0f, 0.0f, 1.0f }, // 黄色
    { 1.0f, 0.0f, 1.0f, 1.0f }, // 紫色
    { 0.0f, 1.0f, 1.0f, 1.0f }, // 水色
    { 1.0f, 1.0f, 0.0f, 1.0f }, // 黄色
    { 1.0f, 0.0f, 1.0f, 1.0f }, // 紫色
    { 0.0f, 1.0f, 1.0f, 1.0f }, // 水色
    { 1.0f, 1.0f, 0.0f, 1.0f }, // 黄色
    { 1.0f, 0.0f, 1.0f, 1.0f }, // 紫色
};

/// 色データ:立方体
const glm::vec4 colCube[] = {
    { 1, 1, 1, 1}, { 1, 1, 1, 1}, { 1, 1, 1, 1}, { 1, 1, 1, 1},
    { 1, 1, 1, 1}, { 1, 1, 1, 1}, { 1, 1, 1, 1}, { 1, 1, 1, 1},
};

/// 色データ:木
const glm::vec4 colTree[] = {
    // 木(葉)
    { 1, 1, 1, 1},
    { 1, 1, 1, 1},
    { 1, 1, 1, 1},
    { 1, 1, 1, 1},
    { 1, 1, 1, 1},
    { 1, 1, 1, 1},

    // 木(幹)
    { 1, 1, 1, 1},
    { 1, 1, 1, 1},
    { 1, 1, 1, 1},
    { 1, 1, 1, 1},
    { 1, 1, 1, 1},
    { 1, 1, 1, 1},
};

/// 色データ:建物
const glm::vec4 colWarehouse[] = {
    { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 },
    { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 }, { 1, 1, 1, 1 },
    { 1, 1, 1, 1 }, { 1, 1, 1, 1 },
};

/// テクスチャ座標データ:四角形
const glm::vec2 tcRectangle[] = 
{
    { 0.0f, 0.0f}, { 1.0f, 0.0f}, { 1.0f, 1.0f},
    { 1.0f, 1.0f}, { 0.0f, 1.0f}, { 0.0f, 0.0f},
};

/// テクスチャ座標データ:三角形
const glm::vec2 tcTriangle[] = 
{
    { 0.0f, 0.0f}, { 1.0f, 0.0f}, { 0.5f, 1.0f},
    { 0.0f, 0.0f}, { 1.0f, 0.0f}, { 0.5f, 1.0f},
    { 0.0f, 0.0f}, { 1.0f, 0.0f}, { 0.5f, 1.0f},
};

/// テクスチャ座標データ:立方体
const glm::vec2 tcCube[] = 
{
    { 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f},
    { 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f}, { 0.0f, 0.0f},
};

/// テクスチャ座標データ:木
const glm::vec2 tcTree[] = 
{
    // 木(葉)
    { 0.5f, 1.0f},
    { 0.0f, 0.5f},
    { 0.25f, 0.5f},
    { 0.5f, 0.5f},
    { 0.75f, 0.5f},
    { 1.0f, 0.5f},

    // 木(幹)
    { 0.5f, 0.5f},
    { 0.0f, 0.0f},
    { 0.25f, 0.0f},
    { 0.5f, 0.0f},
    { 0.75f, 0.0f},
    { 1.0f, 0.0f},
};

/// テクスチャ座標データ:建物
const glm::vec2 tcWarehouse[] = 
{
    { 0.0f, 0.0f}, { 0.25f, 0.0f}, { 0.5f, 0.0f}, { 0.75f, 0.0f}, { 1.0f, 0.0f},
    { 0.0f, 0.5f}, { 0.25f, 0.5f}, { 0.5f, 0.5f}, { 0.75f, 0.5f}, { 1.0f, 0.5f},
    { 0.25f, 1.0f}, { 0.0f, 1.0f},
};

/// インデックスデータ:四角形
const GLushort indexRectangle[] = 
{
    0 , 1, 2, 3, 4, 5,
};

/// インデックスデータ:三角形
const GLushort indexTriangle[] = 
{
    2, 1, 0, 5, 4, 3, 8, 7, 6,
};

/// インデックスデータ:立方体
const GLushort indexCube[] = 
{
    0, 1, 2, 2, 3, 0, 4, 5, 1, 1, 0, 4,
    5, 6, 2, 2, 1, 5, 6, 7, 3, 3, 2, 6,
    7, 4, 0, 0, 3, 7, 7, 6, 5, 5, 4, 7,
};

/// インデックスデータ:木
const GLushort indexTree[] = 
{
     0, 1, 2, 0, 2, 3, 0, 3, 4, 0, 4, 5, 1, 4, 3, 3, 2, 1, // 葉
     6, 7, 8, 6, 8, 9, 6, 9,10, 6,10,11, 7,10, 9, 9, 8, 7, // 幹
};

/// インデックスデータ:建物
const GLushort indexWarehouse[] = 
{
     0, 1, 6, 6, 5, 0,
     1, 2, 7, 7, 6, 1,
     2, 3, 8, 8, 7, 2,
     3, 4, 9, 9, 8, 3,
     5, 6,10,10,11, 5,
};

// 画像データ.
const int imageGroundWidth = 8; // 画像の幅.
const int imageGroundHeight = 8; // 画像の高さ.
const GLuint X = 0xff'18'18'18; // 黒.
const GLuint W = 0xff'ff'ff'ff; // 白.
const GLuint R = 0xff'10'10'e0; // 赤.
const GLuint B = 0xff'e0'10'10; // 青.
const GLuint imageGround[imageGroundWidth * imageGroundHeight] = 
{
      X, B, B, B, X, W, W, W,
      X, B, B, B, X, W, W, W,
      X, B, B, B, X, W, W, W,
      X, X, X, X, X, X, X, X,
      W, W, X, R, R, R, X, W,
      W, W, X, R, R, R, X, W,
      W, W, X, R, R, R, X, W,
      X, X, X, X, X, X, X, X,
};

const GLuint imageTriangle[6 * 6] = 
{
     X, W, X, W, X, W,
     X, W, X, W, X, W,
     X, W, X, W, X, W,
     X, W, X, W, X, W,
     X, W, X, W, X, W,
     X, W, X, W, X, W,
};

const GLuint G = 0xff'10'80'10; // 緑.
const GLuint D = 0xff'40'a0'40; // 茶色.
const GLuint imageGreen[8 * 8] = 
{
     G, G, G, G, G, G, G, G,
     G, D, G, G, G, G, G, G,
     G, G, G, G, G, G, G, G,
     G, G, G, G, G, D, G, G,
     G, G, G, G, G, G, G, G,
     G, G, G, G, G, G, G, G,
     G, G, G, G, G, G, G, G,
     G, G, G, G, G, G, G, G,
};

const GLuint P = 0xff'60'60'60;
const GLuint imageRoad[8 * 8] = 
{
      P, P, P, P, P, P, P, P,
      P, W, P, P, P, P, P, P,
      P, P, P, P, P, P, W, P,
      P, P, P, P, P, P, P, P,
      P, P, P, P, P, P, P, P,
      P, P, P, P, P, P, P, P,
      P, P, P, W, P, P, P, P,
      P, P, P, P, P, P, P, P,
};

/// マップデータ.
int mapData[16][16] = 
{
      { 2,2,2,2,2,2,2,2,0,0,1,1,0,0,2,2},
      { 2,2,2,2,2,2,2,2,0,0,1,1,0,0,2,2},
      { 2,2,0,0,0,0,2,2,2,2,2,2,0,0,2,2},
      { 2,2,0,0,0,0,2,2,2,2,2,2,0,0,2,2},
      { 2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2},
      { 2,2,2,2,2,2,0,0,0,0,0,0,2,2,2,2},
      { 2,2,0,0,2,2,2,2,2,2,0,0,2,2,0,0},
      { 2,2,0,0,2,2,2,2,2,2,0,0,2,2,0,0},
      { 2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2},
      { 2,2,2,2,0,0,0,0,2,2,2,2,2,2,2,2},
      { 0,0,2,2,2,2,0,0,0,0,0,0,0,0,2,2},
      { 0,0,2,2,2,2,0,0,0,0,0,0,0,0,2,2},
      { 2,2,0,0,0,0,1,1,1,1,0,0,2,2,2,2},
      { 2,2,0,0,0,0,1,1,1,1,0,0,2,2,2,2},
      { 2,2,2,2,2,2,1,1,1,1,2,2,2,2,0,0},
      { 2,2,2,2,2,2,1,1,1,1,2,2,2,2,0,0},
};

/// オブジェクトマップデータ.
int objectMapData[16][16] = 
{
      { 0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 1, 3, 0, 0},
      { 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 4, 1, 0, 0},
      { 0, 0, 4, 1, 2, 1, 0, 0, 0, 0, 0, 0, 1, 3, 0, 0},
      { 0, 0, 1, 3, 1, 2, 0, 0, 0, 0, 0, 0, 4, 1, 0, 0},
      { 0, 0, 0, 0, 0, 0, 2, 2, 1, 1, 1, 1, 0, 0, 0, 0},
      { 0, 0, 0, 0, 0, 0, 2, 3, 1, 3, 1, 4, 0, 0, 0, 0},
      { 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 4, 1, 0, 0, 1, 4},
      { 0, 0, 1, 3, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 1},
      { 0, 0, 0, 0, 2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
      { 0, 0, 0, 0, 1, 4, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0},
      { 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 1, 0, 0},
      { 4, 1, 0, 0, 0, 0, 3, 1, 3, 1, 1, 3, 1, 4, 0, 0},
      { 0, 0, 3, 1, 1, 4, 0, 0, 0, 0, 4, 1, 0, 0, 0, 0},
      { 0, 0, 1, 1, 3, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1},
      { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3},
};

//// アクターの配列.
//std::vector<std::shared_ptr<Actor>> actors;

/**
* エントリーポイント.
*/
int main()
{
    GameEngine::Initialize();
    GameEngine& engine = GameEngine::Get();

    // アクターの配列.
    std::vector<std::shared_ptr<Actor>>& actors = engine.GetActors();

    // VAOを作成する.
    PrimitiveBuffer& primitiveBuffer = engine.GetPrimitiveBuffer();

    // 描画データを追加する.
    primitiveBuffer.AddFromObjFile("Res/Ground.obj");
    primitiveBuffer.AddFromObjFile("Res/Rectangle.obj");
    primitiveBuffer.AddFromObjFile("Res/Triangle.obj");
    primitiveBuffer.AddFromObjFile("Res/Cube.obj");
    primitiveBuffer.AddFromObjFile("Res/Tree.obj");
    primitiveBuffer.AddFromObjFile("Res/Warehouse.obj");
    primitiveBuffer.AddFromObjFile("Res/tank/Tiger_I.obj");
    primitiveBuffer.AddFromObjFile("Res/tank/T34.obj");
    primitiveBuffer.AddFromObjFile("Res/house/HouseRender.obj");
    primitiveBuffer.AddFromObjFile("Res/Bullet.obj");
    primitiveBuffer.AddFromObjFile("Res/house/broken-house.obj");
    primitiveBuffer.AddFromObjFile("Res/Plane.obj");

    // パイプライン・オブジェクトを作成する.
   /* ProgramPipeline pipeline("Res/FragmentLighting.vert", "Res/FragmentLighting.frag");
    if (!pipeline.IsValid()) {
        return 1;
    }*/

    // uniform変数の位置.
    const GLint locMatTRS = 0;
    const GLint locMatModel = 1;

    // 座標変換行列の回転角度.
    float degree = 0;

    // テクスチャを作成.
    std::shared_ptr<Texture> texGround(new Texture("Res/RoadTiles.tga"));
    std::shared_ptr<Texture> texTriangle(new Texture("Res/Triangle.tga"));
    std::shared_ptr<Texture> texGreen(new Texture("Res/Green.tga"));
    std::shared_ptr<Texture> texRoad(new Texture("Res/Road.tga"));
    std::shared_ptr<Texture> texTree(new Texture("Res/Tree.tga"));
    std::shared_ptr<Texture> texWarehouse(new Texture("Res/Building.tga"));
    std::shared_ptr<Texture> texTank(new Texture("Res/tank/PzVl_Tiger_I.tga"));
    std::shared_ptr<Texture> texTankT34(new Texture("Res/tank/T-34.tga"));
    std::shared_ptr<Texture> texBrickHouse(new Texture("Res/house/House38UVTexture.tga"));
    std::shared_ptr<Texture> texBullet(new Texture("Res/Bullet.tga"));
    std::shared_ptr<Texture> texHouse2(new Texture("Res/house/broken-house.tga"));

    // サンプラを作成.
    //std::shared_ptr<Sampler> sampler(new Sampler(GL_REPEAT));

    // マップに配置する物体の表示データ.
    struct ObjectData 
    {
        const char* name;
        Primitive prim;
        const std::shared_ptr<Texture> tex;
        float scale = 1.0f;
        glm::vec3 ajustment = glm::vec3(0);
        Box collider;
    };

    // 画面端にコライダーを設定
    actors.push_back(std::shared_ptr<Actor>(new Actor{ "Wall", primitiveBuffer.Get(3), texTriangle,
      glm::vec3(-36, 0, -34), glm::vec3(1, 2, 32), 0.0f, glm::vec3(0) }));
    actors.back()->collider = Box{ glm::vec3(0, 0, 0), glm::vec3(1, 4, 64) };
    actors.back()->isStatic = true;

    actors.push_back(std::shared_ptr<Actor>(new Actor{ "Wall", primitiveBuffer.Get(3), texTriangle,
      glm::vec3(30, 0, -34), glm::vec3(1, 2, 32), 0.0f, glm::vec3(0) }));
    actors.back()->collider = Box{ glm::vec3(0, 0, 0), glm::vec3(1, 4, 64) };
    actors.back()->isStatic = true;

    actors.push_back(std::shared_ptr<Actor>(new Actor{ "Wall", primitiveBuffer.Get(3), texTriangle,
      glm::vec3(-34, 0, -36), glm::vec3(32, 2, 1), 0.0f, glm::vec3(0) }));
    actors.back()->collider = Box{ glm::vec3(0, 0, 0), glm::vec3(64, 4, 1) };
    actors.back()->isStatic = true;

    actors.push_back(std::shared_ptr<Actor>(new Actor{ "Wall", primitiveBuffer.Get(3), texTriangle,
      glm::vec3(-34, 0, 30), glm::vec3(32, 2, 1), 0.0f, glm::vec3(0) }));
    actors.back()->collider = Box{ glm::vec3(0, 0, 0), glm::vec3(64, 4, 1) };
    actors.back()->isStatic = true;

    // 描画する物体のリスト.
    const Box col1 = { glm::vec3(-1.75f, 0, -1.75f), glm::vec3(1.75f, 2, 1.75f) };
    const ObjectData objectList[] =
    {
      { "", Primitive(), 0 },    // なし
      { "Tree", primitiveBuffer.Get(4), texTree }, // 木
      { "Warehouse", primitiveBuffer.Get(5), texWarehouse, 1, {}, col1 }, // 建物
      { "BrickHouse", primitiveBuffer.Get(8), texBrickHouse, 3, glm::vec3(-2.6f, 2.0f, 0.8f),
        Box{ glm::vec3(-3, 0, -2), glm::vec3(3, 3, 2) } }, // 建物
      { "House2", primitiveBuffer.Get(10), texHouse2, 1, {},
        Box{ glm::vec3(-2.5f, 0, -3.5f), glm::vec3(2.5f, 3, 3.5f) } }, // 建物
    };

    // 木を植える.
    for (int y = 0; y < 16; ++y) 
    {
        for (int x = 0; x < 16; ++x) {
            const int objectNo = objectMapData[y][x];
            if (objectNo <= 0 || objectNo >= std::size(objectList)) {
                continue;
            }
            const ObjectData p = objectList[objectNo];

            // 四角形が4x4mなので、xとyを4倍した位置に表示する.
            const glm::vec3 position(x * 4 - 32, 0, y * 4 - 32);

            actors.push_back(std::shared_ptr<Actor>(new Actor{ p.name, p.prim, p.tex,
              position, glm::vec3(p.scale), 0.0f, p.ajustment }));
            actors.back()->collider = col1;// p.collider;
            actors.back()->isStatic = true;
        }
    }

    // マップを(-20,-20)-(20,20)の範囲に描画.
    const std::shared_ptr<Texture> mapTexList[] = { texGreen, texGround, texRoad };
    for (int y = 0; y < 16; ++y)
    {
        for (int x = 0; x < 16; ++x) 
        {
            // 四角形が4x4mなので、xとyを4倍した位置に表示する.
            const glm::vec3 position(x * 4 - 32, 0, y * 4 - 32);

            const int textureNo = mapData[y][x];
            actors.push_back(std::shared_ptr<Actor>(new Actor{ "Ground", primitiveBuffer.Get(0), mapTexList[textureNo],
              position, glm::vec3(1), 0.0f, glm::vec3(0) }));
            actors.back()->collider = Box{ glm::vec3(-2, -10, -2), glm::vec3(2, 0, 2) };
            actors.back()->isStatic = true;
        }
    }

    // エレベーター
    {
        const glm::vec3 position(4 * 4 - 20, -1, 4 * 4 - 20);
        actors.push_back(std::shared_ptr<Actor>(new ElevatorActor{
          "Elevator", primitiveBuffer.Get(0), mapTexList[0],
          position, glm::vec3(1), 0.0f, glm::vec3(0) }));
        actors.back()->velocity.y = 1;
        //actors.back()->collider = Box{ glm::vec3(-2, -10, -2), glm::vec3(2, 0, 2) };
        actors.back()->isStatic = true;
    }

    // 三角形のパラメータ
    actors.push_back(std::shared_ptr<Actor>(new Actor{ "Triangle", primitiveBuffer.Get(2), texTriangle,
      glm::vec3(0, 0, -5), glm::vec3(1), 0.0f, glm::vec3(0) }));
    // 立方体のパラメータ
    actors.push_back(std::shared_ptr<Actor>(new Actor{ "Cube", primitiveBuffer.Get(3), texTriangle,
      glm::vec3(0, 0, -4), glm::vec3(1), 0.0f, glm::vec3(0) }));

    std::shared_ptr<GameMap> gamemap(new GameMap(16, 16, -32, -32, 4, &objectMapData[0][0]));
    std::vector<glm::ivec2> route = gamemap->FindRoute(glm::ivec2(7, 15), glm::ivec2(10, 0));

    // ゲームマネージャを作成
    GameManager::Initialize();
    GameManager& manager = GameManager::Get();

    // メインループ.
    double loopTime = engine.GetTime();     // 1/60秒間隔でループ処理するための時刻
    double diffLoopTime = 0;             // 時刻の差分
    const float deltaTime = 1.0f / 60.0f;// 時間間隔
    glm::vec3 cameraPosition = glm::vec3(0, 20, 20); // カメラの座標
    glm::vec3 cameraTarget = glm::vec3(0, 0, 0);     // カメラの注視点の座標
    while (!engine.WindowShouldClose())
    {
        // 現在時刻を取得
        const double curLoopTime = engine.GetTime();
        // 現在時刻と前回時刻の差を、時刻の差分に加算
        diffLoopTime += curLoopTime - loopTime;
        // 時刻を現在時刻に更新
        loopTime = curLoopTime;
        // 時刻の差分が1/60秒未満なら、ループの先頭に戻る
        if (diffLoopTime < deltaTime) 
        {
            continue;
        }
        if (diffLoopTime > 20.0 / 60.0) 
        {
            diffLoopTime = deltaTime;
        }

        //
        // ゲーム状態を更新する
        //

        engine.NewFrame();
        for (; diffLoopTime >= deltaTime; diffLoopTime -= deltaTime) 
        {
            engine.UpdateActors(deltaTime);
            manager.Update(deltaTime);
            engine.PostUpdateActors();

            // アクターの衝突判定を行う

            engine.UpdatePhysics(deltaTime);
            manager.UpdateCamera();
            engine.UpdateCamera();

            for (int i = 0; i < actors.size(); ++i)
            {
                actors[i]->isOnActor = false;
            }
          
            // 削除待ちのアクターを削除する
            engine.RemoveDeadActors();  
        }
        manager.UpdateUI();

        //
        // ゲーム状態を描画する
        //
        
        engine.RenderDefault();
        engine.RenderUI();
        engine.PostRender();        

        engine.SwapBuffers();
    }

    GameManager::Finalize();
    GameEngine::Finalize();

    return 0;
}
