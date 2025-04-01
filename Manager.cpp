#include "Manager.h"



void GameManager::InsertActorInMap(Actor* actor)
{
	string name = actor->GetName();
	this->actors.insert({ name, shared_ptr<Actor>(actor) });
}

const map<string, shared_ptr<Actor>> GameManager::GetActors()
{
	return this->actors;
}

shared_ptr<Actor> GameManager::GetUser()
{
	for (auto actor : this->actors)
	{
		if (actor.first.find("User") == 0)
			return actor.second;
	}
	return nullptr;
}

shared_ptr<Actor> GameManager::GetNPC()
{
	for (auto actor : this->actors)
	{
		if (actor.first.find("N") == 0)
		{
			return actor.second;
		}
	}
	return nullptr;
}

vector<shared_ptr<Actor>> GameManager::GetMonster()
{
	vector<shared_ptr<Actor>> MonsterVec;
	for (auto actor : this->actors)
	{
		if (actor.first.find("M") == 0)
		{
			MonsterVec.push_back(actor.second);
		}
	}
	return MonsterVec;
}

void GameManager::RemoveActorByName(string name)
{
	this->actors.erase(name);	
}

void GameManager::ModifyActorPosByName(string name, Pos modifyedPos)
{
	this->actors.find("User")->second->SetPos(modifyedPos);	
}

void MapManager::GenerateMap()
{
	this->CopyMap = this->OriginalMap;
	for (const auto entity : GameManager::GetInstance().GetActors())
	{
		if (entity.first == "User")
			this->CopyMap[entity.second->GetPos().y][entity.second->GetPos().x] = 5;
		else
			this->CopyMap[entity.second->GetPos().y][entity.second->GetPos().x] = 6;
	}
}

void MapManager::ShowMap()
{
	this->GenerateMap();

	this->MoveCursorToTopLeft();

	for (int y = 0; y < this->CopyMap.size(); y++)
	{
		for (int x = 0; x < this->CopyMap[y].size(); x++)
		{
			if (this->CopyMap[y][x] == 0)
				cout << "□";
			else if (this->CopyMap[y][x] == 1)
				cout << "■";
			else if (this->CopyMap[y][x] == 2)
				cout << "▦";
			else if (this->CopyMap[y][x] == 5)
				cout << "★";
			else if (this->CopyMap[y][x] == 6)
				cout << "◆";
		}
		cout << endl;
	}
}

Pos MapManager::GetMapSize()
{
	return Pos(this->SizeX, this->SizeY);
}

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
	}

}

void UpdateManager::PlayerUpdate(Pos mapSize)
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
	}

	if (bBoundaryCheck(currentPos, mapSize.x, mapSize.y))
	{
		
		user->SetPos(currentPos);
		user->SetDirection(dir);
	}
}

void UpdateManager::PlayerUpdateLoop(Pos mapSize, bool* gamestate, double frametick)
{
	while (*gamestate)
	{
		this->PlayerUpdate(mapSize);
		Sleep(frametick);
	}
}

void UpdateManager::NPCUpdate(Pos mapSize)
{
	shared_ptr<Actor> npc = GameManager::GetInstance().GetNPC();

	// NPC는 없을수도 있으므로 그냥 에러처리 없음
	if (npc == nullptr)
		return;

	// 그리고 현재 프로젝트에선 NPC는 이동을 하지 않으므로
	// 추후 코드는 이 아래에 작성할 것
}


void UpdateManager::MonsterUpdate(Pos mapSize)
{
	vector<shared_ptr<Actor>> monsters = GameManager::GetInstance().GetMonster();
	
	// 마찮가지로 유저가 죽였거나 처음 스폰에는 몬스터가 없으므로 그냥 에러처리 생략
	if (monsters.size() == 0)
		return;

	for (shared_ptr<Actor> monster : monsters)
	{
		// 몹은 랜덤하게 움직이므로 랜덤으로 방향값 받아옴
		DIRECTION dir = static_cast<DIRECTION>(iRandNum(4));
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

		if (bBoundaryCheck(currentPos, mapSize.x, mapSize.y))
		{
			monster->SetPos(currentPos);
			monster->SetDirection(dir);
		}
	}
}