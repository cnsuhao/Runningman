#include "SkillBanana.h"
#include "Player/PlayerStatus.h"
#include "Player/Player.h"


SkillBanana::SkillBanana(Player* pPlayer) :
	SkillBase(pPlayer)
{
	m_SkillConsume = 1;
}

void SkillBanana::useSkill()
{
	//if (CircleRunScene.m_Track != null && m_pPlayer!=null)
	//{
	//	CircleRunScene.m_Track.CreateTrap(m_pPlayer.rotation, (uint)TrapType.TRAP_BANANA);
	//}
}