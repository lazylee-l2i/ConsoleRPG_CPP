#include "ZeldaCore.h"

using namespace std;

void Init()
{
	GameManager::GetInstance().InsertActorInMap(new Actor("User", Pos(5, 3), (int)5));

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
	
	MapManager::GetInstance().ShowMap();

	UpdateManager* uManage = new UpdateManager();
	thread userInput(&UpdateManager::PlayerUpdateLoop, uManage, flag, timer->GetFrameTickTime());
	
	timer->LoopStart();
	while (*flag)
	{	
		Sleep(timer->GetFrameTickTime());
		MapManager::GetInstance().ShowMap();
		if(timer->GetFrameCount() >= 10)
		{
			timer->LoopStart();
			Update(uManage);
			InteractionManager::GetInstance().CheckMonsterCollision();
		}
		//InteractionManager::GetInstance().CheckUserCollision();
		
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