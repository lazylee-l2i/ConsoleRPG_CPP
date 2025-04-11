#include "GameManager.h"
#include <iostream>

void GameManager::PlayerMoveMap()
{
    GET_SINGLE(EntityManager).RemoveAllByType(EEntityType::MONSTER);
    GET_SINGLE(EntityManager).RemoveAllByType(EEntityType::ITEM);
    GET_SINGLE(MapManager).Init();
    auto player = static_cast<Player*>(GET_SINGLE(EntityManager).FindEntityByName("Player").get());

    Pos before = player->GetPos() - player->GetDirectionByPos();
    Pos after(MAP_WIDTH - before.x - 1, MAP_HEIGHT - before.y - 1);
    player->SetPos(after);

    int MOB_GEN_NUM = static_cast<int>(MAP_WIDTH * MAP_HEIGHT * 0.01 * AUTO_MOB_GEN_PERCENT);

    for (int i = 0; i < MOB_GEN_NUM; i++)
    {
        Pos rand = GET_SINGLE(MapManager).GetRandomEmptyPos();
        GET_SINGLE(EntityManager).CreateEntity(EEntityType::MONSTER, rand);
    }
}

void GameManager::PlayerCommandMod()
{
    system("cls");
    std::cout << "====== <Player Command Mode> =====" << std::endl;
    std::cout << "/> ";
    std::string cmd;
    std::cin >> cmd;
    std::vector<string> command = StringTokenizer(cmd);
    if (command[0] == "exit")
    {
        this->CommandFlag = false;
    }
    else if (command[0] == "cheat")
    {
        GET_SINGLE(EntityManager).RemoveAllByType(EEntityType::MONSTER);
        GET_SINGLE(EntityManager).RemoveAllByType(EEntityType::ITEM);
        GET_SINGLE(MapManager).GenerateMap();
        Pos pos(1, 1);
        for (int i = 0; i < ((MAP_WIDTH - 2) * 2); i++)
        {   
            GET_SINGLE(EntityManager).CreateEntity(EEntityType::ITEM, pos, 2);
            pos.x += 1;
            if (pos.x == MAP_WIDTH - 1)
            {
                pos.x = 1;
                pos.y += 1;
            }
        }
    }
    else if (command[0] == "clearGame")
    {

    }
    else if (command[0] == "heal")
    {

    }
    else if (command[0] == "killall")
    {

    }
    system("cls");

}

std::vector<std::string> StringTokenizer(std::string _cmd)
{
    std::vector<std::string> Token;
    std::string txt = "";
    for (auto _c : _cmd)
    {
        if (txt != " ")
        {
            txt += _c;
        }
        else
        {
            Token.push_back(txt);
            txt = "";
        }
    }
    Token.push_back(txt);
    return Token;
}