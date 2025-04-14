#pragma once
#include "Entity.h"
#include "Actor.h"
#include "Item.h"
#include "Utill.h"

#include <vector>
#include <memory>

class Player;
class Item;

// EntityManager include Simple Factory Pattern
// EntityManager Control All Entity using Vector Container
// Container Element type is shared pointer for memory

class EntityManager
{
	DECLARE_SINGLE(EntityManager)
private:
	// Entity Container, using shared pointer for memory leak.
	vector<shared_ptr<Entity>> ActiveEntities;
	// Monster ID, for Generating Monster Entity
	int monsterIndex = 0;
public:
	// Create Entity & Push Entity Container
	void CreateEntity(EEntityType type, const Pos& pos = Pos(0,0), const int _opt = 0);
	// Create Item Randomly
	shared_ptr<Item> CreateRandomItem(const Pos& pos, const int _opt = 0);

	// Remove Methods
	void RemoveEntityByName(const string& name);
	void RemoveAllByType(EEntityType type);
	void RemoveByPos(Pos pos);

	// Getter
	// Get Player Direction Pos for Mapping Attack Symbol
	EInputType GetPlayerDirecion();
	// Get Player Entity Reference
	shared_ptr<Player> GetPlayer();

	// Get All Entity
	vector<shared_ptr<Entity>>& GetAllEntities();

	// Find Method using Pos & Name
	shared_ptr<Entity> FindEntityByName(const string& name);
	shared_ptr<Entity> FindEntityByPos(const Pos& pos);

};

