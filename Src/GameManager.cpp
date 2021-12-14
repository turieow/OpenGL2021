/**
* @file GameManager.cpp
*/
#include "GameManager.h"
#include "GameEngine.h"
#include "Actor/PlayerActor.h"
#include "Actor/T34TankActor.h"
#include <imgui.h>
#include <iostream>

namespace {

    GameManager* manager = nullptr;

}

/**
* ゲームマネージャの初期化
*/
bool GameManager::Initialize()
{
    if (!manager) {
        void UpdateUI();
        manager = new GameManager;
    }
    return true;
}

/**
* ゲームマネージャの終了
*/
void GameManager::Finalize()
{
    if (manager) {
        delete manager;
        manager = nullptr;
    }
}

/**
* ゲームエンジンを取得する
*/
GameManager& GameManager::Get()
{
    return *manager;
}

/**
*
*/
void GameManager::SetState(State s)
{
    static const char* names[] = {
      "start", "playing", "gameclear", "gameover" };
    std::cout << names[static_cast<int>(state)] <<
        "->" << names[static_cast<int>(s)] << "\n";

    state = s;
}

/**
* ゲームの動作状態を更新する
*/
void GameManager::Update(float deltaTime)
{
    GameEngine& engine = GameEngine::Get();
    switch (state) {
    case State::start:
        SpawnPlayer();
        SpawnEnemies();
        {
            std::shared_ptr<Actor> gamestart(new Actor{ "GameStart",
              engine.GetPrimitive("Res/Plane.obj"),
              engine.LoadTexture("Res/GameStart.tga"),
              glm::vec3(0, 5, 0), glm::vec3(800.0f, 200.0f, 1.0f), 0.0f, glm::vec3(0) });
            gamestart->lifespan = 3;
            gamestart->isStatic = true;
            gamestart->layer = Layer::UI;
            engine.AddActor(gamestart);
        }
        SetState(State::playing);
        break;

    case State::playing:
        if (playerTank->isDead) {
            std::shared_ptr<Actor> gameover(new Actor{ "GameOver",
              engine.GetPrimitive("Res/Plane.obj"),
              engine.LoadTexture("Res/GameOver.tga"),
              glm::vec3(0), glm::vec3(700, 200, 1), 0, glm::vec3(0) });
            gameover->isStatic = true;
            gameover->layer = Layer::UI;
            engine.AddActor(gameover);
            SetState(State::gameover);
        }
        else {
            bool allKill = true;
            for (int i = 0; i < enemies.size(); ++i) {
                if (!enemies[i]->isDead) {
                    allKill = false;
                    break;
                }
            }
            if (allKill) {
                std::shared_ptr<Actor> gameclear(new Actor{ "GameClear",
                  engine.GetPrimitive("Res/Plane.obj"),
                  engine.LoadTexture("Res/GameClear.tga"),
                  glm::vec3(0), glm::vec3(700, 200, 1), 0.0f, glm::vec3(0) });
                gameclear->isStatic = true;
                gameclear->layer = Layer::UI;
                engine.AddActor(gameclear);
                SetState(State::gameclear);
            }
        }
        break;

    case State::gameclear:
        if (engine.GetKey(GLFW_KEY_ENTER)) {
            std::shared_ptr<Actor> gameclear = engine.FindActor("GameClear");
            if (gameclear) {
                gameclear->isDead = true;
            }
            SetState(State::start);
        }
        break;

    case State::gameover:
        if (engine.GetKey(GLFW_KEY_ENTER)) {
            std::shared_ptr<Actor> gameover = engine.FindActor("GameOver");
            if (gameover) {
                gameover->isDead = true;
            }
            SetState(State::start);
        }
        break;
    }
}

// カメラの状態を更新する
void GameManager::UpdateCamera()
{
    GameEngine& engine = GameEngine::Get();

    // プレイヤー戦車を斜めに見下ろすように、カメラの位置と向きを設定する
    {
        std::shared_ptr<Actor> target = Find(engine.GetActors(), "Tiger-I");
        if (target) {
            Camera& camera = engine.GetCamera();
            camera.position = target->position + glm::vec3(0, 20, 20);
            camera.target = target->position;
        }
    }
}

// UIの状態を更新する
void GameManager::UpdateUI()
{
    static bool show_demo_window = true;
    static bool show_another_window = false;
    static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    // 2. Show a simple window that we create ourselves. We use a Begin/End pair to created a named window.
    {
        static float f = 0.0f;
        static int counter = 0;

        ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

        ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
        ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state
        ImGui::Checkbox("Another Window", &show_another_window);

        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
        ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

        if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
            counter++;
        ImGui::SameLine();
        ImGui::Text("counter = %d", counter);

        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();
    }
}

/**
* プレイヤーの戦車を生成する
*/
void GameManager::SpawnPlayer()
{
    // 以前に作成したタイガーI戦車を削除
    if (playerTank) {
        playerTank->isDead = true;
    }

    // 新しいタイガーI戦車を作成
    playerTank.reset(new PlayerActor{ glm::vec3(0), glm::vec3(1), 0.0f });

    // タイガーI戦車をゲームエンジンに登録
    GameEngine::Get().AddActor(playerTank);
}

/**
* 敵戦車を生成
*/
void GameManager::SpawnEnemies()
{
    GameEngine& engine = GameEngine::Get();

    // 以前に作成したT-34戦車を削除
    for (int i = 0; i < enemies.size(); ++i) {
        if (enemies[i]) {
            enemies[i]->isDead = true;
        }
    }
    enemies.clear();

    // 新しいT-34戦車を作成
    const glm::vec3 t34PosList[] = {
      glm::vec3(-5, 0, 0),
      glm::vec3(15, 0, 0),
      glm::vec3(-10, 0, -5),
    };
    for (auto& pos : t34PosList) {
        std::string name("T-34[");
        name += '0' + static_cast<char>(&pos - t34PosList);
        name += ']';
        std::shared_ptr<Actor> enemy(new T34TankActor{ name.c_str(),
          engine.GetPrimitive("Res/tank/T34.obj"),
          engine.LoadTexture("Res/tank/t-34.tga"),
          pos, glm::vec3(1), 0.0f, glm::vec3(-0.78f, 0, 1.0f), playerTank });
        enemy->collider = Box{ glm::vec3(-1.5f, 0, -1.5f), glm::vec3(1.5f, 2.5f, 1.5f) };
        enemy->mass = 36'000;
        enemies.push_back(enemy);
    }

    // T-34戦車をゲームエンジンに登録
    for (int i = 0; i < enemies.size(); ++i) {
        engine.AddActor(enemies[i]);
    }
}
