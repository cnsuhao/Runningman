#include "SkillBoard.h"
#include "Player/PlayerStatus.h"
#include "Player/Player.h"

#include "Scene/GameScene.h"
#include "Trap/TrapBase.h"
#include "Scene/Track.h"


SkillBoard::SkillBoard(Player* pPlayer) :
	SkillBase(pPlayer)
{
	m_SkillConsume = 1;
}

void SkillBoard::useSkill()
{
	GameScene* gs = (GameScene*)(GameScene::GetNode());
	if (gs != nullptr && gs->m_Track != nullptr && m_pPlayer != nullptr)
	{
		gs->m_Track->CreateTrap(m_pPlayer->getRotation(),TrapType::TRAP_BANANA);
	}
}