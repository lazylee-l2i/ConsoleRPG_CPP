#include "ZeldaCore.h"
#include "Manager.h"

void GameManager::InsertActorInMap(Actor* actor)
{
	string name = actor->GetName();
	this->actors.insert({ name, shared_ptr<Actor>(actor) });
}

void GameManager::AutoGenerateMonster(int n)
{
	string name = "M";
	Pos size = MapManager::GetInstance().GetMapSize();
	/*for (int i = 0; i < n; i++)
	{
		string monsterName = name + to_string(i + 1);
		this->InsertActorInMap(new Actor(monsterName, Pos(size.x, size.y), 2));
	}*/

	int idx = 1;
	while (this->GetMonster().size() != n)
	{
		string monsterName = name + to_string(idx);
		Actor *tempMon = new Actor(monsterName, Pos(iRandNum(size.x), iRandNum(size.y)), 2);
		if (this->PostCheckBeforeGenerateMonster(tempMon->GetPos()))
		{
			this->InsertActorInMap(tempMon);
			idx += 1;
		}
		else
		{
			delete tempMon;
		}
	}
}

bool GameManager::PostCheckBeforeGenerateMonster(Pos monsterPos)
{
	if (this->GetUser()->GetPos() == monsterPos)
		return false;
	for (const Pos& pos : MapManager::GetInstance().GetAllObstaclePos())
	{
		if (pos == monsterPos)
			return false;
	}
	return true;
}

void GameManager::SpawnItemAfterMonsterDead(Pos pos)
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

shared_ptr<Item> GameManager::GetInventory()
{
	return this->questBag;
}

vector<shared_ptr<Item>> GameManager::GetDrop()
{
	return this->dropedItems;
}

void GameManager::RemoveDeadActor()
{
	for (auto it = this->actors.begin(); it != actors.end();)
	{
		if (it->second->GetHP() <= 0)
		{ 
			this->SpawnItemAfterMonsterDead(it->second->GetPos());
			it = this->actors.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void GameManager::ModifyActorPosByName(string name, Pos modifyedPos)
{
	this->actors.find("User")->second->SetPos(modifyedPos);	
}

MapManager::MapManager()
{
	this->FindAllObstaclePos();
}

void MapManager::GenerateMap()
{
	this->CopyMap = this->OriginalMap;
	for (const auto entity : GameManager::GetInstance().GetActors())
	{
		if (entity.first == "User")
		{
			this->CopyMap[entity.second->GetPos().y][entity.second->GetPos().x] = 5;
			if (this->PlayerAttack)
			{
				Pos attackPos = entity.second->GetPos() + entity.second->GetDirectionByPos();
				this->CopyMap[attackPos.y][attackPos.x] = 7;
				this->PlayerAttack = false;
			}
		}
		else
		{
			this->CopyMap[entity.second->GetPos().y][entity.second->GetPos().x] = 6;
		}
	}
	for (const auto item : GameManager::GetInstance().GetDrop())
	{
		Pos pos = item->GetItemPos();
		string itemName = item->GetItemName();
		if (itemName == "heart")
		{ 
			this->CopyMap[pos.y][pos.x] = 8;
		}
		else if (itemName == "Quest")
		{
			this->CopyMap[pos.y][pos.x] = 11;
		}
	}
}

void MapManager::ShowMap()
{
	this->GenerateMap();
	
	this->MoveCursorToTopLeft();
	// 0 = Road, 1 = Stone, 2 = Exit
	// 5 = Player, 6 = Monster, 7 = Player Attack
	// 8 = NPC, 9 = small heart(hp + 1), {10_WIP = Big heart(MAX HP + 1)}
	// 11 = Quest item;
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
			else if (this->CopyMap[y][x] == 7)
			{
				DIRECTION dir = GameManager::GetInstance().GetUser()->GetDirection();
				switch (dir)
				{
				case DIRECTION::UP:
					cout << "▲";
					break;
				case DIRECTION::DOWN:
					cout << "▼";
					break;
				case DIRECTION::LEFT:
					cout << "◀";
					break;
				case DIRECTION::RIGHT:
					cout << "▶";
					break;
				}
			}
			else if (this->CopyMap[y][x] == 8)
			{
				cout << "♥";
			}
			else if (this->CopyMap[y][x] == 11)
			{
				cout << "♬";
			}
		}
		cout << endl;
	}
}

Pos MapManager::GetMapSize()
{
	return Pos(this->SizeX, this->SizeY);
}

int MapManager::GetMapPosValue(Pos pos)
{
	return this->OriginalMap[pos.y][pos.x];
}

const vector<Pos>& MapManager::GetAllObstaclePos()
{
	return this->ObstacleVector;
}

void MapManager::FindAllObstaclePos()
{
	vector<Pos> ObstaclePos;
	for (int i = 0; i < this->OriginalMap.size(); i++)
	{
		for (int j = 0; j < this->OriginalMap[0].size(); j++)
		{
			if (OriginalMap[i][j] == 2)
				ObstaclePos.push_back(Pos(j, i));
		}
	}
	this->ObstacleVector = ObstaclePos;
	
}

void MapManager::SetAttackTile(Pos pos)
{
	if(this->ActorObstacleCheck(pos))
		this->CopyMap[pos.y][pos.x] = 7;
}


// operation table by return value
// 0 = not found problem
// 1 = found obstacle
// 2 = found exit
MAPVALUETYPE MapManager::MapDataCheck(const Pos pos)
{
	int MapData = this->GetMapPosValue(pos);
	// 지금 당장은 타입만 받아 전환해주는
	// Converter 역할을 하는 메소드입니다만
	// 나중에 Converting 과정에서 필요하면 추가 작성할 수 있게
	// 칸을 나눠놓았음.
	if (MapData == 1)
	{ 
		return MAPVALUETYPE::OBSTACLE;
	}
	else if (MapData == 2)
	{ 
		return MAPVALUETYPE::EXIT;
	}
	else
	{
		return MAPVALUETYPE::ROAD;
	}
}

bool MapManager::ActorObstacleCheck(Pos& pos, string actorName)
{
	// Map Boundary Check
	if (pos.x < 0)
	{
		pos.x = 0;
		return false;
	}
	else if (pos.x > (this->SizeX - 1))
	{
		pos.x = (this->SizeX - 1);
		return false;
	}

	if (pos.y < 0)
	{
		pos.y = 0;
		return false;
	}
	else if (pos.y > (this->SizeY - 1))
	{
		pos.y = (this->SizeY - 1);
		return false;
	}

	// Attack Symbol의 경우 이름이 없으므로
	// 아래 연산은 생략하고 바로 리턴
	if (actorName == "")
		return true;

	// Map Obstacle Check
	switch (this->MapDataCheck(pos))
	{
	case MAPVALUETYPE::ROAD:
		return true;
	case MAPVALUETYPE::OBSTACLE:
		return false;
	case MAPVALUETYPE::EXIT:
		// 이거는 User만 진입하게
		// Map Change 하고 User의 위치만 이동시키고
		// Monster는 삭제하고 다시 재배치
		if (actorName == "User")
		{
			// Code Here
		}
		break;
	}

	return true;
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

	if (MapManager::GetInstance().ActorObstacleCheck(currentPos, user->GetName()))
	{
		user->SetPos(currentPos);
		user->SetDirection(dir);
	}
	
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

		if (MapManager::GetInstance().ActorObstacleCheck(currentPos, monster->GetName()))
		{
			monster->SetPos(currentPos);
			monster->SetDirection(dir);
		}
	}
	
}

void InteractionManager::CheckAllActorCollision()
{
	// Get All Actor Reference
	shared_ptr<Actor> player = GameManager::GetInstance().GetUser();
	shared_ptr<Actor> npc = GameManager::GetInstance().GetNPC();
	vector<shared_ptr<Actor>> monsters = GameManager::GetInstance().GetMonster();
	
	/*
	 이 메소드에서는 Collision관련만 체크
	 유저가 몬스터에게 겹쳐졌을 때 피격 이벤트와
	 몬스터와 몬스터가 겹치지 않게 분리하는데 중점을 둠
	 User의 Attack은 다른 메소드에서 구현
	*/
	
	// User vs Monster Collision
	if (player != nullptr)
	{

	}

	// User vs NPC Collision
	if (npc != nullptr)
	{

	}

	// Monster to Monster Collision
	if (monsters.size() != 0)
	{

	}
}

// User vs (Monster or Item)
void InteractionManager::CheckUserCollision()
{
	shared_ptr<Actor> player = GameManager::GetInstance().GetUser();
	vector<shared_ptr<Actor>> monsters = GameManager::GetInstance().GetMonster();
	if (monsters.size() == 0)
		return;

	for (const auto monster : monsters)
	{
		if (player->GetPos() == monster->GetPos())
		{
			//player->SetHP(player->GetHP() - 1);
			player->ActorKnockBack(monster->GetDirectionByPos());
		}
	}

	for (auto item : GameManager::GetInstance().GetDrop())
	{
		if (player->GetPos() == item->GetItemPos())
		{
			if (item->GetItemName() == "heart")
			{
				player->SetHP(player->GetHP() + item->GetItemEffectValue());
			}
			else if (item->GetItemName() == "Quest")
			{
				shared_ptr<Item> item = GameManager::GetInstance().GetInventory();
				if (item->GetItemCount() < item->GetItemStackSize())
				{
					item->PlusItemCount();
					if (item->GetItemCount() == 10)
					{
						GameManager::GetInstance().ChangeGameState();
					}
				}
			}
		}
	}
}

// Monster to Monster
void InteractionManager::CheckMonsterCollision()
{
	vector<shared_ptr<Actor>> monsters = GameManager::GetInstance().GetMonster();
	int size = monsters.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = i+1; j < size; j++)
		{
			if (monsters[i]->GetPos() == monsters[j]->GetPos())
			{
				monsters[i]->ActorKnockBack();
			}
		}
	}
}

// User vs NPC
// NPC는 움직이지 않으므로 비워놓았으나
// 추후 NPC도 AI에 따라 움직이게 만드려면 Manager.cpp에 정의하기
void InteractionManager::CheckNPCCollision()
{
}

void InteractionManager::UserAttackMonster()
{
	shared_ptr<Actor> user = GameManager::GetInstance().GetUser();
	vector<shared_ptr<Actor>> monsters = GameManager::GetInstance().GetMonster();

	for (auto monster : monsters)
	{
		if ((user->GetPos() + user->GetDirectionByPos()) == monster->GetPos())
		{
			monster->SetHP(monster->GetHP() - user->GetAttack());
			monster->ActorKnockBack(user->GetDirectionByPos());
			if (monster->GetHP() <= 0)
			{
				GameManager::GetInstance().RemoveDeadActor();
			}
		}
	}
}


