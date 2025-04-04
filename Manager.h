#pragma once
#include "ZeldaCore.h"
#include "Item.h"
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
	shared_ptr<Item> questBag = make_shared<Item>(2, Pos(0,0));
	bool* bGameState = nullptr;

public:
	static GameManager& GetInstance()
	{
		static GameManager GM;
		return GM;
	}
	// 코드에서 직접 삽입할 때 사용
	void InsertActorInMap(shared_ptr<Actor> actor);

	// 자동으로 몬스터를 n만큼 생성하게 해주는 메소드
	void AutoGenerateMonster(int n);

	// 생성되기 전 장애물이나 이미 생성된 몬스터와 겹치는지 확인하는 메소드
	bool PostCheckBeforeGenerateMonster(Pos monsterPos);

	// 몬스터가 죽으면 일정 확률에 따라 아이템을 생성해주는 메소드
	void SpawnItemAfterMonsterDead(const Pos& pos);
	
	// 플레이어가 맵을 이동 할 떄 사용하는 메소드
	void PlayerMoveMap(Pos maxSize);

	const map<string, shared_ptr<Actor>> GetActors();
	shared_ptr<Actor> GetPlayer();
	shared_ptr<Actor> GetNPC();
	vector<shared_ptr<Actor>> GetMonster();
	shared_ptr<Item> GetInventory();
	vector<shared_ptr<Item>>& GetDrop();

	void RemoveDeadActor(string name);
	void RemoveAllMonster();
	void RemoveFieldEntity();
	void RemoveItemFromPos(Pos pos);

	void ChangeGameState() { *this->bGameState = false; }

	bool bGetGameState() { return this->bGameState; }
	void SetGameState(bool* flag) { this->bGameState = flag; }
};



class MapManager
{
private:
	MapManager();
	MapManager(const MapManager& ref) {}
	MapManager& operator=(const MapManager& ref) {}
	~MapManager() {}

	//===============  Map Data  ====================
	vector<vector<int>> DefaultMap;
	vector<vector<int>> BaseMap;
	vector<vector<int>> CopyMap;

	int SizeX = 0;
	int SizeY = 0;
	
	bool PlayerAttack = false;
	vector<Pos> ObstacleVector;

	void GenerateMap();
	void GenObstacle();
	void MapDataSetting();

	// Cursor Move & Rewrite Screen method
	void MoveCursorToTopLeft();

public:
	static MapManager& GetInstance()
	{
		static MapManager MM;
		return MM;
	}
	void ShowMap();
	MAPVALUETYPE MapDataCheck(const Pos pos);
	bool EntityObstacleCheck(Pos& pos, string actorName="");
	bool EntityBoundaryCheck(Pos& pos);
	Pos CheckKnockBackPos(shared_ptr<Actor> Target, shared_ptr<Actor> Attacker = nullptr);

	Pos GetMapSize();
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