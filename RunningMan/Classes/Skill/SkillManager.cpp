#include "SkillManager.h"

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
		break;
	case SKILL_BOARD:
		break;
	case SKILL_ANGER:
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