#include "ZeldaCore.h"

#include <thread>
using namespace std;

void Debug()
{
    // 초기화
    

    auto entityManager = GET_SINGLE(EntityManager);

    // 엔티티 생성
    entityManager->CreateEntity(EEntityType::PLAYER, Pos(2, 2));
    entityManager->CreateEntity(EEntityType::MONSTER);
    entityManager->CreateEntity(EEntityType::ITEM, Pos(3, 3));

    // 루프
    for (int i = 0; i < 10; ++i)
    {
        

        // 플레이어 이동 (테스트용)
        auto player = dynamic_pointer_cast<Player>(entityManager->FindEntityByName("Player"));
        if (player)
        {
            player->Move(); // 내부에서 SetPos() 처리
            system("cls");
        }
        for (auto& entity : GET_SINGLE(EntityManager)->GetAllEntities())
        {
            if (Monster* monster = dynamic_cast<Monster*>(entity.get()))
            {
                monster->Move();
            }
        }

        // 디버그 출력
        entityManager->DebugPrintEntities();
        
    }
}

void Init()
{
    // 초기화
    srand(static_cast<unsigned int>(time(0)));

    auto entityManager = GET_SINGLE(EntityManager);

    // 엔티티 생성
    entityManager->CreateEntity(EEntityType::PLAYER, Pos(2, 2));

    GET_SINGLE(MapManager)->Init();
    GET_SINGLE(GameManager)->Init();

    GET_SINGLE(TimeManager)->SetFrameTick(20);
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