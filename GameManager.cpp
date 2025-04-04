#include "ZeldaCore.h"
#include "Manager.h"

void GameManager::InsertActorInMap(shared_ptr<Actor> actor)
{
	string name = actor->GetName();
	this->actors.insert({ name, shared_ptr<Actor>(actor) });
}

void GameManager::AutoGenerateMonster(int n)
{
	string name = "M";
	Pos size = MapManager::GetInstance().GetMapSize();

	int idx = 1;
	while (this->GetMonster().size() != n)
	{
		string monsterName = name + to_string(idx);
		//Actor* tempMon = new Actor(monsterName, Pos(iRandNum(size.x), iRandNum(size.y)), 2);
		shared_ptr<Actor> tempMon = make_shared<Actor>(monsterName, Pos(iRandNum(size.x), iRandNum(size.y)), 2);
		if (this->PostCheckBeforeGenerateMonster(tempMon->GetPos()))
		{
			this->InsertActorInMap(tempMon);
			idx += 1;
		}
		else
		{
			
		}
	}
}

bool GameManager::PostCheckBeforeGenerateMonster(Pos monsterPos)
{
	if (this->GetPlayer()->GetPos() == monsterPos)
		return false;
	Pos maxSize = MapManager::GetInstance().GetMapSize();
	if (monsterPos.x == 0 || monsterPos.x == maxSize.x-1 || monsterPos.y == 0 || monsterPos.y == maxSize.y-1)
	{
		return false;
	}

	for (const Pos& pos : MapManager::GetInstance().GetAllObstaclePos())
	{
		if (pos == monsterPos)
			return false;
	}
	return true;
}

void GameManager::SpawnItemAfterMonsterDead(const Pos& pos)
{
	int num = iRandNum(100);
	if (num >= 0 && num < 10)
	{
		this->dropedItems.push_back(shared_ptr<Item>(new Item(2, pos)));
	}
	else if (num >= 10 && num < 50)
	{
		this->dropedItems.push_back(shared_ptr<Item>(new Item(1, pos)));
	}
	else
	{
		// 여기는 스폰이 안되는 공간
		// 하지만 필요하다면 여기에 다른 이벤트를 추가해 보는것도 재밌을듯?
		// ex. 몬스터 2마리 다시 스폰
	}
	//this->dropedItems.push_back(shared_ptr<Item>(new Item(2, pos)));
	
}

void GameManager::PlayerMoveMap(Pos maxSize)
{
	Pos userPos = this->GetPlayer()->GetPos();
	userPos.x = maxSize.x - userPos.x - 1;
	userPos.y = maxSize.y - userPos.y - 1;
	this->GetPlayer()->SetPos(userPos);

}

const map<string, shared_ptr<Actor>> GameManager::GetActors()
{
	return this->actors;
}

shared_ptr<Actor> GameManager::GetPlayer()
{
	for (auto actor : this->actors)
	{
		if (actor.first.find("Player") == 0)
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

shared_ptr<Item> GameManager::GetInventory()
{
	return this->questBag;
}

vector<shared_ptr<Item>>& GameManager::GetDrop()
{
	return this->dropedItems;
}

void GameManager::RemoveDeadActor(string name)
{
	auto monster = this->actors.find(name);
	if (monster == this->actors.end()) 
		return;

	Pos pos = monster->second->GetPos();
	this->SpawnItemAfterMonsterDead(pos);
	this->actors.erase(name);

}

void GameManager::RemoveAllMonster()
{
	// actors = map<string, shared_ptr<Actor>>
	if (this->GetMonster().size() == 0)
		return;
	for (auto it = this->actors.begin(); it != actors.end();)
	{
		if (it->second->GetName().find("M") == 0)
		{
			it = this->actors.erase(it);
		}
		else
		{ 
			++it;
		}
	}
}

void GameManager::RemoveFieldEntity()
{
	this->RemoveAllMonster();
	this->dropedItems.clear();
}

void GameManager::RemoveItemFromPos(Pos pos)
{
	for (auto it = this->dropedItems.begin(); it != this->dropedItems.end();)
	{
		if (it->get()->GetItemPos() == pos)
		{
			it = this->dropedItems.erase(it);
		}
		else
		{
			++it;
		}
	}
}


