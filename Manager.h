#pragma once
#include "ZeldaCore.h"
#include <Windows.h>

using namespace std;

class Actor;
struct Pos;

class GameManager
{
private:
	GameManager() {};
	GameManager(const GameManager& ref) {};
	GameManager& operator=(const GameManager& ref) {}
	~GameManager() {};
	map<string, shared_ptr<Actor>> actors;
	bool* bGameState = nullptr;
public:
	static GameManager& GetInstance()
	{
		static GameManager s;
		return s;
	}
	void InsertActorInMap(Actor* actor);
	void SetGameState(bool* flag) { this->bGameState = flag; }
	
	const map<string, shared_ptr<Actor>> GetActors();
	shared_ptr<Actor> GetUser();
	shared_ptr<Actor> GetNPC();
	vector<shared_ptr<Actor>> GetMonster();

	void RemoveActorByName(string name);

	void ModifyActorPosByName(string name, Pos modifyedPos);
	void ChangeGameState() { *this->bGameState = false; }

	bool bGetGameState() { return this->bGameState; }
};

class MapManager
{
private:
	vector<vector<int>> OriginalMap = {
		{1,1,1,1,2,2,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{2,0,0,0,0,0,0,0,0,2},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,2,2,1,1,1,1}
	};
	vector<vector<int>> CopyMap;

	int SizeX = this->OriginalMap.size();
	int SizeY = this->OriginalMap[0].size();
	void GenerateMap();
	void MoveCursorToTopLeft()
	{
		COORD coord = { 0,0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}

public:
	void ShowMap();
	Pos GetMapSize();
};

class UpdateManager
{
private:
	DIRECTION PlayerInput();
public:
	void PlayerUpdate(Pos mapSize);
	void PlayerUpdateLoop(Pos mapSize, bool* gamestate, double frametick);
	void NPCUpdate(Pos mapSize);
	void MonsterUpdate(Pos mapSize);
};