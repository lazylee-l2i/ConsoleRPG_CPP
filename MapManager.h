#pragma once
#include <vector>

#include "Utill.h"

#include "Entity.h"
#include "EntityManager.h"
#include "TileCollector.h"
#include "GameManager.h"

#include "Item.h"


class MapManager
{
    DECLARE_SINGLE(MapManager)

private:
    std::vector<int> DefaultMap = vector<int>(MAP_WIDTH * MAP_HEIGHT, 0);
    std::vector<int> GeneratedMap = vector<int>(MAP_WIDTH * MAP_HEIGHT, 0);
    TileCollector tileCollector;

public:
    void Init();
    void GenerateMap();
    void GenObstacle(int percentage = 10);
    int GetIndex1DPosition(int x, int y);
    Pos GetRandomEmptyPos();
    TileCollector GetTileCollector() { return tileCollector; }

    void MoveCursorToTopLeft();
    void ShowMap();

    void SetTile(int x, int y, EMapTileType tileType);
    EMapTileType GetTile(int x, int y);
};
