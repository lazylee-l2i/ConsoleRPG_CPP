#include "ZeldaLibrary.h"
#include <conio.h>
/*
	10x10 맵을 디폴트로 일단 ㄱ



*/

bool boundaryCheck(Pos _attack)
{
	int iAttackPos = _attack.Make1D();
	if (iAttackPos >= 0 && iAttackPos < 10)
		return false;
	for (int i = 1; i < 10; i++)
	{
		if (iAttackPos == 10 * i || iAttackPos == 19 * i)
			return false;
	}
	return true;
}


void mapShow(vector<int> map, Pos _player, Pos _attack, bool isAttack)
{
	

	int playerPos = _player.Make1D();
	bool attackFlag = boundaryCheck(_attack) && isAttack;
	int attackPos = _attack.Make1D();

	for (int i = 0; i < 100; i++)
	{
		if (i == playerPos)
		{ 
			cout << "P";
			continue;
		}
		if ((i == attackPos) && (attackFlag))
		{ 
			cout << "A";
			continue;
		}
		if (map[i] == 3)
			cout << "■";
		else if (map[i] == 0)
			cout << "□";
		
		if (i % 10 == 9)
			cout << endl;
	}
}

int main()
{
	vector<int> map1 = {
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3,
		3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
		3, 0, 0, 0, 0, 0, 0, 0, 0, 3,
		3, 3, 3, 3, 3, 3, 3, 3, 3, 3
	};
	Pos playerPos(5, 5);
	Pos attackPos(0,0);
	//cout << map1.size() << endl;

	bool flag = true;
	bool attackFlag = false;
	while(flag)
	{ 
		char _c = (char)_getch();;
		
		switch (_c)
		{
		case 'w':
			playerPos = playerPos - Pos(0, 1);
			attackPos = playerPos;
			attackPos -= Pos(0, 1);
			//attackFlag = false;
			break;
		case 'a':
			playerPos = playerPos - Pos(1, 0);
			attackPos = playerPos;
			attackPos -= Pos(1, 0);
			//attackFlag = false;
			break;
		case 's':
			playerPos = playerPos + Pos(0, 1);
			attackPos = playerPos;
			attackPos += Pos(0, 1);
			//attackFlag = false;
			break;
		case 'd':
			playerPos = playerPos + Pos(1, 0);
			attackPos = playerPos;
			attackPos += Pos(1, 0);
			//attackFlag = false;
			break;
		case 'p':
			attackFlag = true;
			break;
		case 'o':
			attackFlag = false;
			break;
		case 'q':
			flag = false;
			break;

		}
		system("cls");
		mapShow(map1, playerPos, attackPos, attackFlag);
		
	}

	return 0;
}