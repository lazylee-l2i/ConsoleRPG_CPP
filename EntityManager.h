#pragma once
#include "Entity.h"
#include "Actor.h"
#include "Item.h"

#include <vector>
#include <memory>

class Player;

class EntityManager
{
	DECLARE_SINGLE(EntityManager);
private:
	// 원래는 unorederd_map으로 하려했는데
	// 규모가 작아서 그냥 vector로 진행
	vector<shared_ptr<Entity>> ActiveEntities;
	int monsterIndex = 0;
public:
	void CreateEntity(EEntityType type, const Pos& pos = Pos(0,0));
	void RemoveEntityByName(const string& name);
	void RemoveAllByType(EEntityType type);
	void RemoveByPos(Pos pos);
	EInputType GetPlayerDirecion();
	shared_ptr<Player> GetPlayer();

	vector<shared_ptr<Entity>>& GetAllEntities();
	shared_ptr<Entity> FindEntityByName(const string& name);
	shared_ptr<Entity> FindEntityByPos(const Pos& pos);

	// For Debug
	void DebugPrintEntities();
};

