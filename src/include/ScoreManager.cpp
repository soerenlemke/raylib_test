//
// Created by soeren on 04.11.25.
//

#include "ScoreManager.h"

#include "Block.h"

void ScoreManager::SubscribeToBlock(Block &block) {
    block.SetOnDestroyed([this] { OnBlockDestroyed(); });
}

void ScoreManager::OnBlockDestroyed() {
    score++;
    if (score < 0) score = 0;
}