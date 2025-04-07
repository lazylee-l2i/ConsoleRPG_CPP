#pragma once
#include "Type.h"

#include "Entity.h"
#include "Actor.h"

#include "EntityManager.h"
#include "MapManager.h"



class GameManager
{
	DECLARE_SINGLE(GameManager)
private:
	bool GameLoopFlag = true;
	bool AttackFlag = false;
public:
	void Init() { GameLoopFlag = true; }
	void PlayerMoveMap();
	void ChangeGameLoopFlag() { GameLoopFlag = GameLoopFlag == true ? false : true; }
	bool GetGameLoopFlag() { return GameLoopFlag; }
	void ChangeAttackFlag() { AttackFlag = AttackFlag == true ? false : true; }
	bool GetAttackFlag() { return AttackFlag; }
};