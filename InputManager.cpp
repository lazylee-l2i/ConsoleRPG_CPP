#include "InputManager.h"

bool InputManager::IsAttackKeyPressed()
{
	return AttackKey;
}

void InputManager::AttackKeyRelease()
{
	AttackKey = false;
}

EInputType InputManager::PlayerInput()
{
	char UserInput = static_cast<char>(_getch());
	switch (UserInput)
	{
	case 'w':
		return EInputType::UP;
	case 's':
		return EInputType::DOWN;
	case 'a':
		return EInputType::LEFT;
	case 'd':
		return EInputType::RIGHT;
	case 'q':
		return EInputType::QUIT;
	case ' ':
		AttackKey = true;
		return EInputType::ATTACKCALL;
	case 't':
		return EInputType::COMMAND_MODE;
	default:
		return EInputType::UNDEFINE;
	}
}

EInputType InputManager::MonsterInput()
{
	return static_cast<EInputType>(rand() % 4);
}

int InputManager::GetRandomNum(int n)
{
	return rand() % n;
}

Pos InputManager::GetRandomPos()
{
	Pos pos;
	pos.x = this->GetRandomNum(MAP_WIDTH);
	pos.y = this->GetRandomNum(MAP_HEIGHT);
	return pos;
}
