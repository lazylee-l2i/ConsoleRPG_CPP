#include <iostream>
#include <string>
#include <vector>
#include <time.h>
#include <Windows.h>
#include <random>
#include <conio.h>

#include "Actor.h"
#include "Manager.h"

using namespace std;


int RandNum(int N)
{
	srand(GetTickCount64());
	Sleep(1);
	return (rand() % N);
}

bool boundaryCheck(Pos& pos)
{
	if (pos.x < 0)
	{ 
		pos.x = 0;
		return false;
	}
	else if (pos.x > 9)
	{
		pos.x = 9;
		return false;
	}
	if (pos.y < 0)
	{
		pos.y = 0;
		return false;
	}
	else if (pos.y > 4)
	{
		pos.x = 4;
		return false;
	}

	return true;
}

void MonsterUpdate(Actor& Monster)
{
	Pos current = Monster.GetPos();
	int option = RandNum(5);
	switch (option)
	{
	case 0:
		current.y--;
		break;
	case 1:
		current.y++;
		break;
	case 2:
		current.x--;
		break;
	case 3:
		current.x++;
		break;
	case 4:
		break;
	}
	if (boundaryCheck(current))
		Monster.SetPos(current);
}

void PlayerUpdate(Actor& player, bool& flag)
{
	Pos current = player.GetPos();
	char _c = (char)_getch();
	switch (_c)
	{
	case 'w':
		current.y--;
		break;
	case 's':
		current.y++;
		break;
	case 'a':
		current.x--;
		break;
	case 'd':
		current.x++;
		break;
	case 'q':
		flag = false;
	}

	if (boundaryCheck(current))
		player.SetPos(current);
}

void Update(bool& flag)
{
	for (const auto ptr : GameManager::GetInstance().GetActors())
	{
		if (ptr.lock()->GetName() == "User")
			PlayerUpdate(*ptr.lock(), flag);
		else
			MonsterUpdate(*ptr.lock());
	}

}

vector<vector<int>> GenerateNewMap(vector<vector<int>> map)
{
	vector<vector<int>> temp = map;
	for (const auto entity : GameManager::GetInstance().GetActors())
	{
		if (entity.lock()->GetName() == "User")
			temp[entity.lock()->GetPos().y][entity.lock()->GetPos().x] = 5;
		else
			temp[entity.lock()->GetPos().y][entity.lock()->GetPos().x] = 6;
	}
	return move(temp);
}

void Show(vector<vector<int>> map)
{
	for (int y = 0; y < map.size(); y++)
	{
		for (int x = 0; x < map[y].size(); x++)
		{
			if (map[y][x] == 0)
				cout << "¡à";
			else if (map[y][x] == 1)
				cout << "¡á";
			else if (map[y][x] == 2)
				cout << "¢Ë";
			else if (map[y][x] == 5)
				cout << "¡Ú";
			else if (map[y][x] == 6)
				cout << "¡ß";
		}
		cout << endl;
	}
}

void Play()
{
	bool flag = true;
	Actor Player("User", Pos(5, 3), 5);
	GameManager::GetInstance().SetActorInVector(Player);

	Actor Monster1("M1", Pos(RandNum(4), RandNum(4)), 10);
	Actor Monster2("M2", Pos(RandNum(4), RandNum(4)), 10);
	Actor Monster3("M3", Pos(RandNum(4), RandNum(4)), 10);
	GameManager::GetInstance().SetActorInVector(Monster1);
	GameManager::GetInstance().SetActorInVector(Monster2);
	GameManager::GetInstance().SetActorInVector(Monster3);

	/*vector<shared_ptr<Actor>> Aptr;
	Aptr.push_back(make_shared<Actor>(Player));
	Aptr.push_back(make_shared<Actor>(Monster1));
	Aptr.push_back(make_shared<Actor>(Monster2));
	Aptr.push_back(make_shared<Actor>(Monster3));*/

	vector<vector<int>> map = {
		{1,1,1,1,2,2,1,1,1,1},
		{1,0,0,0,0,0,0,0,0,1},
		{2,0,0,0,0,0,0,0,0,2},
		{1,0,0,0,0,0,0,0,0,1},
		{1,1,1,1,2,2,1,1,1,1}
	};

	Show(GenerateNewMap(map));
	while (flag)
	{
		Update(flag);
		system("cls");
		Show(GenerateNewMap(map));
	}
}

shared_ptr<Actor> make_new_num(int i)
{
	shared_ptr<Actor> ptr;
	Actor a;
	a.SetPos(Pos(i, i));
	ptr = make_shared<Actor>(a);
	return ptr;
}

int main()
{
	Play();
	/*vector<shared_ptr<Actor>> ptr;
	for (int i = 0; i < 10; i++)
		ptr.push_back(make_new_num(i));

	for (auto item : ptr)
	{
		cout << item.use_count() << endl;
		cout << item->GetPos().x << " | " << item->GetPos().y << endl;
	}*/

	return 0;
}