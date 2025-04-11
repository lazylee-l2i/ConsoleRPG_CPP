#include "TileCollector.h"

const vector<pair<EMapTileType, Pos>> TileCollector::CollectTiles() const
{
    vector<pair<EMapTileType, Pos>> TileInfo;
    auto Entities = GET_SINGLE(EntityManager).GetAllEntities();
    for (const auto& entity : Entities)
    {
        // »èÁ¦µÈ Entity
        if (entity == nullptr)
            continue;
        EEntityType Etype = entity->GetType();
        switch (Etype)
        {
            case EEntityType::PLAYER:
            {
                if (Player* player = static_cast<Player*>(entity.get()))
                {
                    if (not player->GetAlive())
                    {
                        TileInfo.push_back({ EMapTileType::PLAYER_DEAD, entity->GetPos() });
                    }
                    else if (player->GetOnHit())
                    {
                        TileInfo.push_back({ EMapTileType::PLAYER_GETHIT, entity->GetPos() });
                        player->SetOnHit(false);
                    }
                    else
                    {
                        TileInfo.push_back({ EMapTileType::PLAYER, entity->GetPos() });
                    }
                }
                

                // When Player Attack, Insert Attack Tile
                if (GET_SINGLE(InputManager).IsAttackKeyPressed())
                {
                    Player* player = static_cast<Player*>(entity.get());
                    Pos attackPos = player->GetAttackPos();
                    TileInfo.push_back({ EMapTileType::ATTACK, attackPos });
                }
                break;
            }
            case EEntityType::MONSTER:
            {
                TileInfo.push_back({ EMapTileType::MONSTER, entity->GetPos() });
                break;
            }
            case EEntityType::ITEM:
            {
                Item* item = static_cast<Item*>(entity.get());
                EItemType Itype = item->GetItemType();
                TileInfo.push_back({ itemSymbols[Itype], item->GetPos() });
                
                break;
            }
            case EEntityType::NPC:
            {
                break;
            }
        }
    }
    return TileInfo;
}
