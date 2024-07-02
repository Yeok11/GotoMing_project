#pragma once
#include "Shy_Define.h"
#include "Shy_Include.h"

void BoardRender(Board& _board);
void TileSelectRender(Pos pos, bool _delete = false);
void EnemyRender();
void PlayerHpRender(Player player);