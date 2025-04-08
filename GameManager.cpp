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

    int MOB_GEN_NUM = MAP_WIDTH * MAP_HEIGHT * 0.01 * AUTO_MOB_GEN_PERCENT;

    for (int i = 0; i < MOB_GEN_NUM; i++)
    {
        Pos rand = GET_SINGLE(MapManager)->GetRandomEmptyPos();
        GET_SINGLE(EntityManager)->CreateEntity(EEntityType::MONSTER, rand);
    }
}

