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
	// Game State bool value
	bool GameLoopFlag = true;
	bool AttackFlag = false;

	// WIP
	bool CommandFlag = false;

public:
	void Init() { GameLoopFlag = true; CommandFlag = false; }
	void PlayerMoveMap();
	void PlayerCommandMod();

	void ChangeGameLoopFlag() { GameLoopFlag = GameLoopFlag == true ? false : true; }
	void ChangeAttackFlag() { AttackFlag = AttackFlag == true ? false : true; }
	
	bool GetGameLoopFlag() { return GameLoopFlag; }
	bool GetCommandFlag() { return CommandFlag; }
	bool GetAttackFlag() { return AttackFlag; }

	// WIP
	void ChangeCommandFlag() { CommandFlag = CommandFlag == true ? false : true; }
};

// WIP
std::vector<std::string> StringTokenizer(std::string _cmd);