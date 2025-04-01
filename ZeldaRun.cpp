#include "ZeldaCore.h"

using namespace std;

void Init()
{
	GameManager::GetInstance().InsertActorInMap(new Actor("User", Pos(5, 3), (int)5));

	GameManager::GetInstance().InsertActorInMap(new Actor("M1", Pos(iRandNum(10), iRandNum(4)), 5));
	GameManager::GetInstance().InsertActorInMap(new Actor("M2", Pos(iRandNum(10), iRandNum(4)), 5));
	GameManager::GetInstance().InsertActorInMap(new Actor("M3", Pos(iRandNum(10), iRandNum(4)), 5));
}

void Update(UpdateManager* manager)
{
	manager->MonsterUpdate(Pos(10, 5));
}

void Play()
{
	Init();

	bool* flag = new bool();
	*flag = true;
	GameManager::GetInstance().SetGameState(flag);

	GameTimer* timer = new GameTimer();
	timer->SetFrameTick(10);
	
	MapManager* Map = new MapManager();
	UpdateManager* uManage = new UpdateManager();
	thread userInput(&UpdateManager::PlayerUpdateLoop, uManage, Pos(10, 5), flag, timer->GetFrameTickTime());

	Map->ShowMap();
	timer->LoopStart();
	while (*flag)
	{	
		Sleep(timer->GetFrameTickTime());
		Map->ShowMap();

		if(timer->GetFrameCount() >= 10)
		{
			timer->LoopStart();
			Update(uManage);
		}
		
	}

	userInput.join();
	delete flag;
}

int main()
{
	Play();
	

	return 0;
}