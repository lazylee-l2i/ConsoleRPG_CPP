#include "MapManager.h"
#include <iostream>
#include <Windows.h>
#include <algorithm>
using namespace std;



int MapManager::GetIndex1DPosition(int x, int y)
{
    return x + y * MAP_WIDTH;
}

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
    int playerHP = GET_SINGLE(EntityManager).GetPlayer()->GetHP();
    int playerQuestCount = GET_SINGLE(EntityManager).GetPlayer()->GetQuestCount();


    for (int y = 0; y < MAP_HEIGHT; y++)
    {
        for (int x = 0; x < MAP_WIDTH; x++)
        {
            switch (static_cast<EMapTileType>(showingMap[y*MAP_WIDTH + x]))
            {
            case EMapTileType::ROAD:
                _map += "  ";
                break;
            case EMapTileType::WALL:
                _map += "¡á";
                break;
            case EMapTileType::EXIT:
                _map += "¢Ë";
                break;
            case EMapTileType::PLAYER:
                _map += "¡Ù";
                break;
            case EMapTileType::MONSTER:
                _map += "¡Þ";
                break;
            case EMapTileType::HEART:
                _map += "¢¾";
                break;
            case EMapTileType::QUEST:
                _map += "¢Ý";
                break;
            case EMapTileType::ATTACK:
                EInputType dir = GET_SINGLE(EntityManager).GetPlayerDirecion();
                switch (dir)
                {
                case EInputType::UP:
                    _map += "¡â";
                    break;
                case EInputType::DOWN:
                    _map += "¡ä";
                    break;
                case EInputType::LEFT:
                    _map += "¢·";
                    break;
                case EInputType::RIGHT:
                    _map += "¢¹";
                    break;
                }
                GET_SINGLE(InputManager).AttackKeyRelease();
                break;
            }
        }
        _map += "\n";
    }
    _map += "HP    : ";
    for (int i = 0; i < playerHP; i++) _map += "¢¾ ";
    for (int i = 0; i < 10 - playerHP; i++) _map += "¢½ ";
    _map += "\nQuest :";
    for (int i = 0; i < playerQuestCount; i++) _map += "¢Ý ";
    _map += "\n";
    cout << _map;
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



