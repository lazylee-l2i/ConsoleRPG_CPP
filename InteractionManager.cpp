#include "ZeldaCore.h"
#include "Manager.h"


// User vs (Monster or Item)
void InteractionManager::CheckUserCollision()
{
	shared_ptr<Actor> player = GameManager::GetInstance().GetPlayer();
	vector<shared_ptr<Actor>> monsters = GameManager::GetInstance().GetMonster();
	vector<shared_ptr<Item>> drops = GameManager::GetInstance().GetDrop();
	Pos pos = player->GetPos();
	

	for (const auto monster : monsters)
	{
		if (pos == monster->GetPos())
		{
			player->SetHP(player->GetHP() - 1);
			
			MapManager::GetInstance().CheckKnockBackPos(player);

		}
	}

	if (drops.size() == 0)
		return;

	for (shared_ptr<Item> item : drops)
	{
		string ItemName = item->GetItemName();
		Pos itemPos = item->GetItemPos();
		if (pos == itemPos)
		{
			if (ItemName == "heart")
			{
				// WIP
				player->SetHP(player->GetHP() + 2);
			}
			else if (ItemName == "quest")
			{
				GameManager::GetInstance().GetInventory()->PlusItemCount();
			}
			GameManager::GetInstance().RemoveItemFromPos(itemPos);
		}
	}
}

// Monster to Monster
void InteractionManager::CheckMonsterCollision()
{
	vector<shared_ptr<Actor>> monsters = GameManager::GetInstance().GetMonster();
	shared_ptr<Actor> player = GameManager::GetInstance().GetPlayer();
	int size = monsters.size();
	for (int i = 0; i < size; i++)
	{
		for (int j = i + 1; j < size; j++)
		{
			if (monsters[i]->GetPos() == monsters[j]->GetPos())
			{
				/*Pos current = monsters[i]->GetPos();

				monsters[i]->ActorKnockBack();
				Pos After = monsters[i]->GetPos();
				if (not MapManager::GetInstance().EntityObstacleCheck(After, monsters[i]->GetName()))
				{
					monsters[i]->SetPos(current);
				}*/
				MapManager::GetInstance().CheckKnockBackPos(monsters[i]);
			}
		}
		if (player->GetPos() == monsters[i]->GetPos())
		{
			MapManager::GetInstance().CheckKnockBackPos(player);
		}
	}
	
}

// User vs NPC
// NPC는 움직이지 않으므로 비워놓았으나
// 추후 NPC도 AI에 따라 움직이게 만드려면 Manager.cpp에 정의하기
void InteractionManager::CheckNPCCollision()
{
}

void InteractionManager::UserAttackMonster()
{
	shared_ptr<Actor> user = GameManager::GetInstance().GetPlayer();
	vector<shared_ptr<Actor>> monsters = GameManager::GetInstance().GetMonster();

	for (auto monster : monsters)
	{
		if ((user->GetPos() + user->GetDirectionByPos()) == monster->GetPos())
		{
			monster->SetHP(monster->GetHP() - user->GetAttack());
			/*Pos current = monster->GetPos();

			monster->ActorKnockBack(user->GetDirectionByPos());
			Pos After = monster->GetPos();
			if (not MapManager::GetInstance().EntityObstacleCheck(After, monster->GetName()))
			{
				monster->SetPos(current);
			}*/
			MapManager::GetInstance().CheckKnockBackPos(monster, user);

			if (monster->GetHP() <= 0)
			{
				GameManager::GetInstance().RemoveDeadActor(monster->GetName());
			}
		}
	}
}
