#include "ZeldaCore.h"

using namespace std;

void Init()
{
	GameManager::GetInstance().InsertActorInMap(new Actor("User", Pos(5, 3), (int)5));

	//GameManager::GetInstance().AutoGenerateMonster(3);
	//GameManager::GetInstance().InsertActorInMap(new Actor("M1", Pos(iRandNum(10), iRandNum(4)), 5));
	//GameManager::GetInstance().InsertActorInMap(new Actor("M2", Pos(iRandNum(10), iRandNum(4)), 5));
	//GameManager::GetInstance().InsertActorInMap(new Actor("M3", Pos(iRandNum(10), iRandNum(4)), 5));
}

void Update(UpdateManager* manager)
{
	manager->MonsterUpdate();
}

void Play()
{
	Init();

	bool* flag = new bool();
	*flag = true;
	GameManager::GetInstance().SetGameState(flag);

	GameTimer* timer = new GameTimer();
	timer->SetFrameTick(10);
	
	UpdateManager* uManage = new UpdateManager();
	thread userInput(&UpdateManager::PlayerUpdateLoop, uManage, flag, timer->GetFrameTickTime());

	MapManager::GetInstance().ShowMap();
	timer->LoopStart();
	while (*flag)
	{	
		Sleep(timer->GetFrameTickTime());
		MapManager::GetInstance().ShowMap();
		if(timer->GetFrameCount() >= 10)
		{
			timer->LoopStart();
			Update(uManage);
		}
		InteractionManager::GetInstance().CheckUserCollision();
		InteractionManager::GetInstance().CheckMonsterCollision();
	}
	userInput.join();

	if (GameManager::GetInstance().GetInventory()->GetItemCount() == 10)
	{
		cout << "당신이 이겼습니다." << endl;
	}

	delete flag;
	delete timer;
	delete uManage;
}

int main()
{
	Play();

	return 0;
}