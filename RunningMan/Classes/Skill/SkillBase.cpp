#include "SkillBase.h"


SkillBase::SkillBase(Player* pPlayer)
{
	m_pPlayer = pPlayer;
}


SkillBase::~SkillBase(void)
{
}

void SkillBase::useSkill()
{
	;
}

int SkillBase::getConsume()
{
	return m_SkillConsume;
}