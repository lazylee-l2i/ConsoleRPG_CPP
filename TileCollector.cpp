#include "TileCollector.h"

const vector<pair<EMapTileType, Pos>> TileCollector::CollectTiles() const
{
    vector<pair<EMapTileType, Pos>> TileInfo;
    auto Entities = GET_SINGLE(EntityManager).GetAllEntities();
    for (const auto& entity : Entities)
    {
        EEntityType Etype = entity->GetType();
        switch (Etype)
        {
            case EEntityType::PLAYER:
            {
                TileInfo.push_back({ EMapTileType::PLAYER, entity->GetPos() });

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
                switch (Itype)
                {
                    case EItemType::HEART:
                    {
                        TileInfo.push_back({ EMapTileType::HEART, entity->GetPos() });
                        break;
                    }
                    case EItemType::QUEST:
                    {
                        TileInfo.push_back({ EMapTileType::QUEST, entity->GetPos() });
                        break;
                    }
                }
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
