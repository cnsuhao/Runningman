#include "SkillManager.h"

#include "Skill/SkillBanana.h"
#include "Skill/SkillBase.h"
#include "Skill/SkillBoard.h"
#include "Skill/SkillAnger.h"



SkillManager* SkillManager::m_Instance = nullptr;

SkillManager* SkillManager::Instance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new SkillManager();
	}

	return m_Instance;
}

SkillManager::SkillManager(void)
{
}


SkillManager::~SkillManager(void)
{
}

SkillBase* SkillManager::CreateSkill(SkillType type, Player* pPlayer)
{
	SkillBase* pSkill = nullptr;

	switch (type)
	{
	case SKILL_BANANA:
		pSkill = new SkillBanana(pPlayer);
		break;
	case SKILL_BOARD:
		pSkill = new SkillBoard(pPlayer);
		break;
	case SKILL_ANGER:
		pSkill = new SkillAnger(pPlayer);
		break;
	case SKILL_SPEEDMAX:
		break;
	case SKILL_FLY:
		break;
	case SKILL_POWERUPTURBO:
		break;
	case SKILL_WAND:
		break;
	case SKILL_USECOFFIN:
		break;
	case SKILL_COFFINTHROW:
		break;
	case SKILL_SUPERANGER:
		break;
	case SKILL_WEAKFLY:
		break;
	case SKILL_NULL:
		break;
	default:
		break;
	}

	return pSkill;
}