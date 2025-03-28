#pragma once
#include "ZeldaLibrary.h"

class SceneManager
{
private:
	SceneManager() {};
	SceneManager(const SceneManager& ref) {}
	SceneManager& operator=(const SceneManager& ref) {}
	~SceneManager() {}
public:
	static SceneManager& GetInstance()
	{
		static SceneManager s;
		return s;
	}

	//===========Scene Manager ¸Ş¼Òµå=============
	void ShowMap();
};