#include "ZeldaCore.h"
#include "Manager.h"

DIRECTION UpdateManager::PlayerInput()
{
	char _c = static_cast<char>(_getch());
	switch (_c)
	{
	case 'w':
		return DIRECTION::UP;
	case 's':
		return DIRECTION::DOWN;
	case 'a':
		return DIRECTION::LEFT;
	case 'd':
		return DIRECTION::RIGHT;
	case 'q':
		return DIRECTION::QUIT;
	case ' ':
		return DIRECTION::ATTACKCALL;
	}
}


void UpdateManager::PlayerUpdate()
{
	shared_ptr<Actor> user = GameManager::GetInstance().GetUser();
	try
	{
		if (user == nullptr)
		{
			throw runtime_error("User가 없음");
		}

	}
	catch (const runtime_error& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}

	DIRECTION dir = this->PlayerInput();

	Pos currentPos = user->GetPos();

	switch (dir)
	{
	case DIRECTION::UP:
		currentPos.y -= 1;
		break;
	case DIRECTION::DOWN:
		currentPos.y += 1;
		break;
	case DIRECTION::LEFT:
		currentPos.x -= 1;
		break;
	case DIRECTION::RIGHT:
		currentPos.x += 1;
		break;
	case DIRECTION::QUIT:
		GameManager::GetInstance().ChangeGameState();
		return;
	case DIRECTION::ATTACKCALL:
		// 어택 관련 InteractionManager 호출하기
		MapManager::GetInstance().SetAttackCall(true);
		InteractionManager::GetInstance().UserAttackMonster();
		return;
	}

	if (MapManager::GetInstance().EntityObstacleCheck(currentPos, user->GetName()))
	{
		if (MapManager::GetInstance().MapDataCheck(currentPos) != MAPVALUETYPE::EXIT)
		{
			user->SetPos(currentPos);
			user->SetDirection(dir);
		}
	}
	InteractionManager::GetInstance().CheckUserCollision();

}

void UpdateManager::PlayerUpdateLoop(bool* gamestate, double frametick)
{
	while (*gamestate)
	{
		this->PlayerUpdate();
		Sleep(frametick);
	}
}

void UpdateManager::NPCUpdate()
{
	shared_ptr<Actor> npc = GameManager::GetInstance().GetNPC();

	// NPC는 없을수도 있으므로 그냥 에러처리 없음
	if (npc == nullptr)
		return;

	// 그리고 현재 프로젝트에선 NPC는 이동을 하지 않으므로
	// 추후 코드는 이 아래에 작성할 것
}


void UpdateManager::MonsterUpdate()
{
	vector<shared_ptr<Actor>> monsters = GameManager::GetInstance().GetMonster();

	// 마찮가지로 유저가 죽였거나 처음 스폰에는 몬스터가 없으므로 그냥 에러처리 생략
	if (monsters.size() == 0)
		return;

	for (shared_ptr<Actor> monster : monsters)
	{
		// 몹은 랜덤하게 움직이므로 랜덤으로 방향값 받아옴
		DIRECTION dir = static_cast<DIRECTION>(iRandNum(4));
		monster->SetDirection(dir);
		Pos currentPos = monster->GetPos();

		switch (dir)
		{
		case DIRECTION::UP:
			currentPos.y -= 1;
			break;
		case DIRECTION::DOWN:
			currentPos.y += 1;
			break;
		case DIRECTION::LEFT:
			currentPos.x -= 1;
			break;
		case DIRECTION::RIGHT:
			currentPos.x += 1;
			break;
			// 몹이 게임 주체자가 아닌데 QUIT을 받았다간 큰일남
			// 그래서 QUIT은 안전하게 지워줌(혹시 모르니까)
		}

		if (MapManager::GetInstance().EntityObstacleCheck(currentPos, monster->GetName()))
		{
			monster->SetPos(currentPos);
			monster->SetDirection(dir);
		}
	}

}