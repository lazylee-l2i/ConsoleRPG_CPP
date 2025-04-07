#include "UpdateManager.h"


void UpdateManager::UpdateMonsters()
{
    auto& entities = GET_SINGLE(EntityManager)->GetAllEntities();

    for (auto& entity : entities)
    {
        if (entity->GetType() != EEntityType::MONSTER)
            continue;

        Pos before = entity->GetPos();
        entity->Update();
        Pos after = entity->GetPos();
        entity->SetPos(before);

        EMapTileType tile = GET_SINGLE(MapManager)->GetTile(after.x, after.y);
        auto target = GET_SINGLE(EntityManager)->FindEntityByPos(after);


        // 벽 또는 출구는 이동 불가 → 롤백
        if (tile == EMapTileType::WALL || tile == EMapTileType::EXIT)
        {
            entity->SetPos(before);
            continue;
        }

        if (target && target->GetType() == EEntityType::MONSTER)
        {
            continue;
        }

        // 해당 위치에 다른 Entity가 있는지 확인
        if (target && target->GetType() == EEntityType::PLAYER)
        {
            entity->SetPos(after); // 이동
            entity->Interact(target.get()); // 상호작용
            continue;
        }

        // 그 외는 이동만 진행
        entity->SetPos(after);
    }
}


void UpdateManager::UpdatePlayer()
{
    auto player = GET_SINGLE(EntityManager)->GetPlayer();
    auto& entities = GET_SINGLE(EntityManager)->GetAllEntities();

    if (GET_SINGLE(GameManager)->GetAttackFlag())
    {
        Pos attackPos = player->GetAttackPos();

        for (auto iter = entities.begin(); iter != entities.end(); ++iter)
        {
            if (iter->get()->GetPos() == attackPos && iter->get()->GetType() == EEntityType::MONSTER)
            {
                player->Attack(iter->get());
                entities.erase(iter);
                GET_SINGLE(GameManager)->ChangeAttackFlag();
                break;
            }
        }
    }

    Pos before = player->GetPos();
    player->Update();
    Pos after = player->GetPos();

    EMapTileType tile = GET_SINGLE(MapManager)->GetTile(after.x, after.y);

    // =========== 중요 =================
    // 걸리는게 있다면 player->SetPos(before)
    // 걸리는게 없다면 그냥 무시하고 진행


    // 벽과 출입구에 대한 조사(콜리전 체크)
    if (tile == EMapTileType::EXIT)
    {
        GET_SINGLE(GameManager)->PlayerMoveMap();
    }
    else if (tile == EMapTileType::WALL)
    {
        player->SetPos(before);
        return;
    }
    // 아이템에 대한 조사
    for (auto iter = entities.begin(); iter != entities.end();)
    {
        auto& entity = *iter;

        Pos entityPos = iter->get()->GetPos();
        if (after != entityPos)
        { 
            ++iter;
            continue;
        }

        EEntityType type = entity->GetType();

        if (type == EEntityType::ITEM)
        {
            player->Interact(entity.get());
            iter = entities.erase(iter);
            return;
        }
        else if (type == EEntityType::MONSTER)
        {
            entity->Interact(player.get());
            player->SetPos(before);
            ++iter;
            continue;
        }
        ++iter;
        
    }


}
