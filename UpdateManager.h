#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "TimeManager.h"
#include "MapManager.h"

class UpdateManager
{
    DECLARE_SINGLE(UpdateManager)
public:
    void UpdateMonsters();
    void UpdatePlayer();
};