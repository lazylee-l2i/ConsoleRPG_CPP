#pragma once
#include "ZeldaCore.h"
#include <Windows.h>


using namespace std;

class Actor;
struct Pos;

enum class MAPVALUETYPE
{
	ROAD,
	OBSTACLE,
	EXIT
};

class GameManager
{
private:
	GameManager() {}
	GameManager(const GameManager& ref) {}
	GameManager& operator=(const GameManager& ref) {}
	~GameManager() { }
	map<string, shared_ptr<Actor>> actors;
	vector<shared_ptr<Item>> dropedItems;
	shared_ptr<Item> questBag = make_shared<Item>(new Item(2, Pos(0,0)));
	bool* bGameState = nullptr;

public:
	static GameManager& GetInstance()
	{
		static GameManager GM;
		return GM;
	}
	// 코드에서 직접 삽입할 때 사용
	void InsertActorInMap(Actor* actor);

	// 자동으로 몬스터를 n만큼 생성하게 해주는 메소드
	void AutoGenerateMonster(int n);

	// 생성되기 전 장애물이나 이미 생성된 몬스터와 겹치는지 확인하는 메소드
	bool PostCheckBeforeGenerateMonster(Pos monsterPos);

	// 몬스터가 죽으면 일정 확률에 따라 아이템을 생성해주는 메소드
	void SpawnItemAfterMonsterDead(Pos pos);

	void SetGameState(bool* flag) { this->bGameState = flag; }
	
	const map<string, shared_ptr<Actor>> GetActors();
	shared_ptr<Actor> GetUser();
	shared_ptr<Actor> GetNPC();
	vector<shared_ptr<Actor>> GetMonster();
	shared_ptr<Item> GetInventory();
	vector<shared_ptr<Item>> GetDrop();

	void RemoveDeadActor();

	void ModifyActorPosByName(string name, Pos modifyedPos);
	void ChangeGameState() { *this->bGameState = false; }

	bool bGetGameState() { return this->bGameState; }
};

class MapManager
{
private:
	MapManager();
	MapManager(const MapManager& ref) {}
	MapManager& operator=(const MapManager& ref) {}
	~MapManager() {}
	bool PlayerAttack = false;
	vector<Pos> ObstacleVector;

	//===============  Map Data  ====================
	vector<vector<int>> Stage1 = {

	};
	//===============================================
	vector<vector<int>> OriginalMap = {
		{1,0,0,0,0,11,11,11,11,0},
		{0,11,11,11,11,11,11,11,11,0},
		{0,0,0,0,0,0,0,1,0,0},
		{1,0,0,0,0,0,0,0,1,0},
		{0,0,0,1,1,1,0,0,1,0}
	};
	vector<vector<int>> CopyMap;

	int SizeY = this->OriginalMap.size();
	int SizeX = this->OriginalMap[0].size();
	void GenerateMap();

	// Cursor Move & Rewrite Screen method
	void MoveCursorToTopLeft()
	{
		COORD coord = { 0,0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

	void FindAllObstaclePos();
	
	MAPVALUETYPE MapDataCheck(const Pos pos);

public:
	static MapManager& GetInstance()
	{
		static MapManager MM;
		return MM;
	}
	void ShowMap();
	bool ActorObstacleCheck(Pos& pos, string actorName="");

	Pos GetMapSize();
	int GetMapPosValue(Pos pos);
	const vector<Pos>& GetAllObstaclePos();
	
	void SetAttackTile(Pos pos);
	void SetAttackCall(bool flag) { this->PlayerAttack = flag; }
};

class InteractionManager
{
private:
	InteractionManager() {}
	InteractionManager(const InteractionManager& ref) {}
	InteractionManager& operator=(const InteractionManager& ref) {}
	~InteractionManager() {}
public:
	static InteractionManager& GetInstance()
	{
		static InteractionManager IM;
		return IM;
	}

	void CheckAllActorCollision();
	void CheckUserCollision();
	void CheckMonsterCollision();
	void CheckNPCCollision();
	void UserAttackMonster();
};

class UpdateManager
{
private:
	DIRECTION PlayerInput();
public:
	void PlayerUpdate();
	void PlayerUpdateLoop(bool* gamestate, double frametick);
	void NPCUpdate();
	void MonsterUpdate();
};