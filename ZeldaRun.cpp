#include "ZeldaCore.h"
#include "StartScreen.h"

#include <unordered_map>
#include <algorithm>
#include <thread>
using namespace std;

void Game();


int main()
{
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

    // MapManager = 기반맵(Default Map) 생성
    // GameManager = Game State 관련 멤버 초기화
    GET_SINGLE(MapManager).Init();
    GET_SINGLE(GameManager).Init();

    // Game 시간 설정 및 시작 시간 설정
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
    // Update 기반으로 Entity 정보 받아서 Field에 출력
    GET_SINGLE(MapManager).ShowMap();
}

void Game()
{
    // 초기화 및 첫 Stage 출력
    // Player 스폰
    Init();
    Render();

    // Player는 Async-비동기 스레드
    thread playerthread(PlayerUpdate);

    // GameManager의 관제에 따라 Loop 실행
    while (GET_SINGLE(GameManager).GetGameLoopFlag())
    {
        // 계속 반복
        Update();
        Render();
        Sleep(static_cast<DWORD>(GET_SINGLE(TimeManager).GetFrameTickTime()));
        
    }

    // 비동기 스레드 종료
    playerthread.join();

    // Game 상태에 따라 결과 출력
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

