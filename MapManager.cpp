#include "MapManager.h"
#include <iostream>
#include <Windows.h>
#include <algorithm>
using namespace std;


// Calculate 2D pos -> 1D pos
int MapManager::GetIndex1DPosition(int x, int y)
{
    return x + y * MAP_WIDTH;
}

// Calculate Empty Tile & Get Random Pos
Pos MapManager::GetRandomEmptyPos()
{
    int n = rand() % (MAP_WIDTH * MAP_HEIGHT - 1);
    while(GeneratedMap[n] == 0)
    {
        Pos pos(n % MAP_WIDTH, n / MAP_WIDTH);
        return pos;
    }
    return Pos();
}

void MapManager::MoveCursorToTopLeft()
{
    COORD coord = { 0,0 };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void MapManager::ShowMap()
{
    this->MoveCursorToTopLeft();
    vector<int> showingMap(MAP_WIDTH * MAP_HEIGHT, 0);

    copy(GeneratedMap.begin(), GeneratedMap.end(), showingMap.begin());
    
    for (auto tile : tileCollector.CollectTiles())
    {
        showingMap[tile.second.y * MAP_WIDTH + tile.second.x] = static_cast<int>(tile.first);
    }

    string _map = "";

    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            if (showingMap[y * MAP_WIDTH + x] == static_cast<int>(EMapTileType::ATTACK))
            {
                EInputType dir = GET_SINGLE(EntityManager).GetPlayerDirecion();
                _map += attackSymbols[dir];
                GET_SINGLE(InputManager).AttackKeyRelease();
            }
            else
            {
                _map += tileSymbols[static_cast<EMapTileType>(showingMap[y * MAP_WIDTH + x])];
            }
        }
        _map += "\n";
    }

    _map += GET_SINGLE(EntityManager).GetPlayer()->ShowPlayerStatus();
    std::cout << _map << std::endl;

    // When Player die. After process for showing screen
    if (not GET_SINGLE(EntityManager).GetPlayer()->GetAlive())
    {
        GET_SINGLE(GameManager).ChangeGameLoopFlag();
    }
    if (GET_SINGLE(EntityManager).GetPlayer()->GetQuestCount() == PLAYER_TARGET_QUEST_COUNT)
    {
        GET_SINGLE(GameManager).ChangeGameLoopFlag();
    }

}

void MapManager::Init()
{
    GenerateMap();
    GenObstacle();
}

void MapManager::GenerateMap()
{
    copy(DefaultMap.begin(), DefaultMap.end(), GeneratedMap.begin());
    for (int y = 0; y < MAP_HEIGHT; ++y)
    {
        for (int x = 0; x < MAP_WIDTH; ++x)
        {
            // Make Boundary
            bool isEdge = (x == 0 || x == MAP_WIDTH - 1 || y == 0 || y == MAP_HEIGHT - 1);
            bool isCenter = (x == MAP_WIDTH / 2 || y == MAP_HEIGHT / 2);

            if (isEdge && isCenter)
            {
                SetTile(x, y, EMapTileType::EXIT);
            }
            else if (isEdge)
            {
                SetTile(x, y, EMapTileType::WALL);
            }
        }
    }
}

void MapManager::SetTile(int x, int y, EMapTileType tileType)
{
    int index = GetIndex1DPosition(x, y);
    GeneratedMap[index] = static_cast<int>(tileType);
}

EMapTileType MapManager::GetTile(int x, int y)
{
    int index = GetIndex1DPosition(x, y);
    return static_cast<EMapTileType>(GeneratedMap[index]);
}

// Generating Obstacle
void MapManager::GenObstacle(int percentage)
{
    int totalCells = MAP_WIDTH * MAP_HEIGHT;
    int numObstacles = totalCells * AUTO_OTC_GEN_PERCENT / 100;

    while (numObstacles > 0)
    {
        int randomX = rand() % MAP_WIDTH;
        int randomY = rand() % MAP_HEIGHT;
        
        if (GetTile(randomX, randomY) == EMapTileType::ROAD)
        {
            SetTile(randomX, randomY, EMapTileType::WALL);
            numObstacles--;
        }
    }
}   



