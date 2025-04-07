#pragma once
#include <vector>
#include <utility>

#include "Entity.h"
#include "Type.h"
#include "EntityManager.h"
#include "InputManager.h"

class TileCollector
{
public:
	TileCollector() {}
	~TileCollector() {}
	const vector<pair<EMapTileType, Pos>> CollectTiles() const;
};