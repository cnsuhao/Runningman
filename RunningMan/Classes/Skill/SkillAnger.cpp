#include "SkillAnger.h"
#include "Player/PlayerStatus.h"
#include "Player/Player.h"


SkillAnger::SkillAnger(Player* pPlayer) :
	SkillBase(pPlayer)
{
	m_SkillConsume = 2;
}

void SkillAnger::useSkill()
{
	if (m_pPlayer != NULL)
	{
		m_pPlayer->m_FSM->SetPlayerStatus(Player_Anger::Instance());
	}
}