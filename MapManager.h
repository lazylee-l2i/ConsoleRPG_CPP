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
    // DefaultMap Include Only Exit, Road, Obstacle Data
    std::vector<int> DefaultMap = vector<int>(MAP_WIDTH * MAP_HEIGHT, 0);

    // GeneratedMap Include Entities Data with Default Map
    std::vector<int> GeneratedMap = vector<int>(MAP_WIDTH * MAP_HEIGHT, 0);

    TileCollector tileCollector;

public:
    // Generate Obstacle & Exit Gate
    void Init();

    // Generate Boundary & Exit
    void GenerateMap();

    // Generate Obstacle, Generating Percentage follow parameter "percentage"
    // Generally GenObstacle Follow defined Const value in "Utill.h"
    void GenObstacle(int percentage = 10);

    // Make 2D Pos TO 1D Position Value
    int GetIndex1DPosition(int x, int y);

    // Generate Random Pos Value except { Obstalce & Exit }
    Pos GetRandomEmptyPos();

    // Collecting Entities Data
    TileCollector GetTileCollector() { return tileCollector; }

    // For prevent blinking screen
    void MoveCursorToTopLeft();

    // Show Map Only
    void ShowMap();

    // Setting Tile by EMapTileType
    void SetTile(int x, int y, EMapTileType tileType);

    // Get Tile Type at Position
    EMapTileType GetTile(int x, int y);
};
