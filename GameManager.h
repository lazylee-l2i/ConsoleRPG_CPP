#pragma once
#include "Utill.h"

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
	bool CommandFlag = false;

	int mapX = MAP_WIDTH;
	int mapY = MAP_HEIGHT;

	int mobP = AUTO_MOB_GEN_PERCENT;
	int obP = AUTO_OTC_GEN_PERCENT;
public:
	void Init() { GameLoopFlag = true; CommandFlag = false; }
	void PlayerMoveMap();
	void PlayerCommandMod();

	void ChangeGameLoopFlag() { GameLoopFlag = GameLoopFlag == true ? false : true; }
	void ChangeAttackFlag() { AttackFlag = AttackFlag == true ? false : true; }
	void ChangeCommandFlag() { CommandFlag = CommandFlag == true ? false : true; }

	bool GetGameLoopFlag() { return GameLoopFlag; }
	bool GetCommandFlag() { return CommandFlag; }
	bool GetAttackFlag() { return AttackFlag; }
};

std::vector<std::string> StringTokenizer(std::string _cmd);