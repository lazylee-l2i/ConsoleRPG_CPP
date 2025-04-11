#include "ZeldaCore.h"
#include "StartScreen.h"

#include <unordered_map>
#include <algorithm>
#include <thread>
using namespace std;

void Game();


int main()
{
    //show_start_screen();
    //
    Game();
    return 0;
}


void Init()
{
    // 초기화
    srand(static_cast<unsigned int>(time(0)));

    // 엔티티 생성
    Pos spawn = Pos(PLAYER_SPAWNPOINT_X, PLAYER_SPAWNPOINT_Y);
    GET_SINGLE(EntityManager).CreateEntity(EEntityType::PLAYER, spawn);

    GET_SINGLE(MapManager).Init();
    GET_SINGLE(GameManager).Init();

    GET_SINGLE(TimeManager).SetFrameTick(GAME_FPS);
    GET_SINGLE(TimeManager).LoopStart();
}


void Update()
{
    if (GET_SINGLE(TimeManager).GetFrameCount() > UPDATE_DURATION_FRAME)
    {
        GET_SINGLE(UpdateManager).UpdateMonsters();
        GET_SINGLE(TimeManager).LoopStart();
    }
    
}

void PlayerUpdate()
{
    while (GET_SINGLE(GameManager).GetGameLoopFlag())
    {
        GET_SINGLE(UpdateManager).UpdatePlayer();
        Sleep(static_cast<DWORD>(GET_SINGLE(TimeManager).GetFrameTickTime()));
    }
}


void Render()
{
    GET_SINGLE(MapManager).ShowMap();
}

void EndGame()
{

}

void Game()
{
    Init();
    Render();

    thread playerthread(PlayerUpdate);

    while (GET_SINGLE(GameManager).GetGameLoopFlag())
    {
        Update();
        Render();
        Sleep(static_cast<DWORD>(GET_SINGLE(TimeManager).GetFrameTickTime()));
        
    }

    playerthread.join();
    auto player = GET_SINGLE(EntityManager).GetPlayer();
    if (player->GetQuestCount() >= PLAYER_TARGET_QUEST_COUNT)
    {
        cout << "Player Win." << endl;
    }
    else if (player->GetHP() <= 0)
    {
        cout << "Player Dead." << endl;
    }
    else
    {
        cout << "Player Give Up." << endl;
    }
}

