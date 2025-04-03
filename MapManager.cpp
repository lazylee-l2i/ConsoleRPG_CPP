#include "ZeldaCore.h"
#include "Manager.h"
#include <algorithm>

MapManager::MapManager()
{
	this->FindAllObstaclePos();
	this->SizeY = 11;
	this->SizeX = 21;
	this->DefaultMap.assign(this->SizeY, vector<int>(this->SizeX, 0));
	this->BaseMap.assign(this->SizeY, vector<int>(this->SizeX, 0));
	this->CopyMap.assign(this->SizeY, vector<int>(this->SizeX, 0));
	
	// 출입구는 각 변의 중심부
	this->DefaultMap[0][static_cast<int>(this->SizeX / 2)] = 2;
	this->DefaultMap[this->SizeY - 1][static_cast<int>(this->SizeX / 2)] = 2;
	this->DefaultMap[static_cast<int>(this->SizeY / 2)][this->SizeX - 1] = 2;
	this->DefaultMap[static_cast<int>(this->SizeY / 2)][0] = 2;

	this->GenerateMap();
}

void MapManager::GenerateMap()
{
	// WIP
	/*
	int mapSelector = iRandNum(10);
	
	// 10%
	if (mapSelector == 0)
	{
		// Event Map Gen _ WIP
		this->GenEventMap();
	}
	// 30%
	else if (mapSelector > 0 && mapSelector < 3)
	{
		// Toxic Map Gen _ WIP
		this->GenToxicMap();
	}
	// 70%
	else
	{
		// Normal Map Gen
		this->GenNormalMap();
	}
	*/
	copy(this->DefaultMap.begin(), this->DefaultMap.end(), this->BaseMap.begin());
	//this->BaseMap = this->DefaultMap;
	this->GenObstacle();
	
}

void MapManager::GenObstacle()
{
	for (int y = 0; y < this->SizeY; y++)
	{
		for (int x = 0; x < this->SizeX; x++)
		{
			if (x == 0 || x == this->SizeX - 1 || y == 0 || y == this->SizeY - 1)
			{
				if (this->BaseMap[y][x] != 2)
				{
					this->BaseMap[y][x] = 1;
				}
			}
			else{
				/*int value = iRandNum(30);
				if (value > 25)
				{
					this->BaseMap[y][x] = 1;
				}*/
			}
		}
	}
	this->FindAllObstaclePos();
}

void MapManager::GenNormalMap()
{
	this->GenObstacle();
}

void MapManager::GenToxicMap()
{
	// WIP
}

void MapManager::GenEventMap()
{
	// WIP
}

void MapManager::MoveCursorToTopLeft()
{
	COORD coord = { 0,0 };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);	
}

void MapManager::RenderMap()
{
	copy(BaseMap.begin(), BaseMap.end(), CopyMap.begin());
	//this->CopyMap = this->BaseMap;
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
		else if (itemName == "quest")
		{
			this->CopyMap[pos.y][pos.x] = 11;
		}
	}
}

void MapManager::ShowMap()
{
	this->RenderMap();

	this->MoveCursorToTopLeft();
	// 0 = Road, 1 = Stone, 2 = Exit
	// 5 = Player, 6 = Monster, 7 = Player Attack
	// 8 = NPC, 9 = small heart(hp + 1), {10_WIP = Big heart(MAX HP + 1)}
	// 11 = quest item;
	string map_data = "";
	for (int y = 0; y < this->CopyMap.size(); y++)
	{
		
		for (int x = 0; x < this->CopyMap[y].size(); x++)
		{
			if (this->CopyMap[y][x] == 0)
				map_data += "  ";
			else if (this->CopyMap[y][x] == 1)
				map_data += "■";
			else if (this->CopyMap[y][x] == 2)
				map_data += "▦";
			else if (this->CopyMap[y][x] == 5)
				map_data += "★";
			else if (this->CopyMap[y][x] == 6)
				map_data += "◆";
			else if (this->CopyMap[y][x] == 7)
			{
				DIRECTION dir = GameManager::GetInstance().GetUser()->GetDirection();
				switch (dir)
				{
				case DIRECTION::UP:
					map_data += "▲";
					break;
				case DIRECTION::DOWN:
					map_data += "▼";
					break;
				case DIRECTION::LEFT:
					map_data += "◀";
					break;
				case DIRECTION::RIGHT:
					map_data += "▶";
					break;
				}
			}
			else if (this->CopyMap[y][x] == 8)
			{
				map_data += "♥";
			}
			else if (this->CopyMap[y][x] == 11)
			{
				map_data += "♬";
			}
		}
		map_data += "\n";
	}
	cout << map_data;
}

Pos MapManager::GetMapSize()
{
	return Pos(this->SizeX, this->SizeY);
}

int MapManager::GetMapPosValue(Pos pos)
{
	return this->BaseMap[pos.y][pos.x];
}

const vector<Pos>& MapManager::GetAllObstaclePos()
{
	return this->ObstacleVector;
}



void MapManager::FindAllObstaclePos()
{
	vector<Pos> ObstaclePos;
	for (int i = 0; i < this->BaseMap.size(); i++)
	{
		for (int j = 0; j < this->BaseMap[0].size(); j++)
		{
			if (BaseMap[i][j] == 1)
				ObstaclePos.push_back(Pos(j, i));
		}
	}
	this->ObstacleVector = ObstaclePos;

}

void MapManager::SetAttackTile(Pos pos)
{
	if (this->EntityObstacleCheck(pos) && this->EntityBoundaryCheck(pos))
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

bool MapManager::EntityObstacleCheck(Pos& pos, string actorName)
{
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
			GameManager::GetInstance().RemoveFieldEntity();
			Pos pos(this->SizeX, this->SizeY);
			GameManager::GetInstance().PlayerMoveMap(pos);
			this->GenerateMap();

			int mobNum = iRandNum(5);
			GameManager::GetInstance().AutoGenerateMonster(mobNum);
			return true;
		}
		return false;
	}

	

	return true;
}

bool MapManager::EntityBoundaryCheck(Pos& pos)
{
	// Map Boundary Check
	if (pos.x < 1)
	{
		pos.x = 1;
		return false;
	}
	else if (pos.x > (this->SizeX - 2))
	{
		pos.x = (this->SizeX - 2);
		return false;
	}

	if (pos.y < 1)
	{
		pos.y = 1;
		return false;
	}
	else if (pos.y > (this->SizeY - 2))
	{
		pos.y = (this->SizeY - 2);
		return false;
	}
	return true;
}

Pos MapManager::CheckKnockBackPos(shared_ptr<Actor> Target, shared_ptr<Actor> Attacker)
{
	Pos TargetCurrentPos = Target->GetPos();
	Pos TargetAfterPos;
	if (Attacker == nullptr)
		TargetAfterPos = Target->ActorKnockBack();
	else
		TargetAfterPos = Target->ActorKnockBack(Attacker->GetDirectionByPos());

	if (this->EntityBoundaryCheck(TargetAfterPos) && this->EntityObstacleCheck(TargetAfterPos, Target->GetName()))
	{
		return TargetAfterPos;
	}
	else
	{
		Target->SetPos(TargetCurrentPos);
		return TargetCurrentPos;
	}

}