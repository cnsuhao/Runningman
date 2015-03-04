#include "SkillBoard.h"
#include "Player/PlayerStatus.h"
#include "Player/Player.h"


SkillBoard::SkillBoard(Player* pPlayer) :
	SkillBase(pPlayer)
{
	m_SkillConsume = 1;
}

void SkillBoard::useSkill()
{
	//if (CircleRunScene.m_Track != null && m_pPlayer != null)
	//{
	//	CircleRunScene.m_Track.CreateTrap(m_pPlayer.rotation, (uint)TrapType.TRAP_BOARD);
	//}
}