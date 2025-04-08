#include "ZeldaCore.h"

#include <Windows.h>
#include <thread>
using namespace std;


void Init()
{
    // 초기화
    srand(static_cast<unsigned int>(time(0)));
    auto entityManager = GET_SINGLE(EntityManager);

    // 엔티티 생성
    entityManager->CreateEntity(EEntityType::PLAYER, Pos(MAP_WIDTH / 2, MAP_HEIGHT / 2));

    GET_SINGLE(MapManager)->Init();
    GET_SINGLE(GameManager)->Init();

    GET_SINGLE(TimeManager)->SetFrameTick(GAME_FPS);
    GET_SINGLE(TimeManager)->LoopStart();
}


void Update()
{
    if (GET_SINGLE(TimeManager)->GetFrameCount() > 10)
    {
        GET_SINGLE(UpdateManager)->UpdateMonsters();
        GET_SINGLE(TimeManager)->LoopStart();
    }
    
}

void PlayerUpdate()
{
    while (GET_SINGLE(GameManager)->GetGameLoopFlag())
    {
        GET_SINGLE(UpdateManager)->UpdatePlayer();
        Sleep(GET_SINGLE(TimeManager)->GetFrameTickTime());
    }
}


void Render()
{
    GET_SINGLE(MapManager)->ShowMap();
}

void Game()
{
    Init();
    Render();


    thread playerthread(PlayerUpdate);

    while (GET_SINGLE(GameManager)->GetGameLoopFlag())
    {
        Update();
        Render();

        Sleep(GET_SINGLE(TimeManager)->GetFrameTickTime());
    }

    playerthread.join();
    auto player = GET_SINGLE(EntityManager)->GetPlayer();
    if (player->GetQuestCount() >= 10)
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

int main()
{
	//srand(static_cast<unsigned int>(GetTickCount64()));
	//Play();
    Game();
    //Debug();
	return 0;
}