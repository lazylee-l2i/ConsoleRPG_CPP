#include "GameManager.h"

void GameManager::PlayerMoveMap()
{
    GET_SINGLE(EntityManager)->RemoveAllByType(EEntityType::MONSTER);
    GET_SINGLE(EntityManager)->RemoveAllByType(EEntityType::ITEM);
    GET_SINGLE(MapManager)->Init();
    auto player = dynamic_cast<Player*>(GET_SINGLE(EntityManager)->FindEntityByName("Player").get());

    Pos before = player->GetPos() - player->GetDirectionByPos();
    Pos after(MAP_WIDTH - before.x - 1, MAP_HEIGHT - before.y - 1);
    player->SetPos(after);

    for (int i = 0; i < AUTO_M_REGEN_NUM; i++)
    {
        Pos rand = GET_SINGLE(MapManager)->GetRandomEmptyPos();
        GET_SINGLE(EntityManager)->CreateEntity(EEntityType::MONSTER, rand);
    }
}

