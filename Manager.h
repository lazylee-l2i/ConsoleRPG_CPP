#pragma once
#include <vector>
#include <iostream>
using namespace std;

class Actor;
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
public:
	void ShowMap();
	void GenerateMap(vector<shared_ptr<Actor>> actors);
};

class GameManager
{
private:
	GameManager() {};
	GameManager(const GameManager& ref) {};
	GameManager& operator=(const GameManager& ref) {}
	~GameManager() {};
	vector<weak_ptr<Actor>> actors;
	
public:
	static GameManager& GetInstance()
	{
		static GameManager s;
		return s;
	}
	void SetActorInVector(Actor& actor)
	{
		this->actors.push_back(make_shared<Actor>(actor));
	}
	const vector<shared_ptr<Actor>>& GetActors()
	{
		return this->actors;
	}
};