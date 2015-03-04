#include "Player_MatchMan.h"
#include "Skill/SkillManager.h"


Player_MatchMan::Player_MatchMan(int id) :
	Player(id)
{
	m_RoleType = "Role_MatchMan";
	//Skill
	m_PlayerSkill_Run = SkillManager::Instance()->CreateSkill(SkillType::SKILL_WAND, this);

	m_PlayerSkill_Jump = SkillManager::Instance()->CreateSkill(SkillType::SKILL_FLY, this);

	m_PlayerSkill_Fall = SkillManager::Instance()->CreateSkill(SkillType::SKILL_POWERUPTURBO, this);

	m_matchManTextureName = "matchManR";


	int frameanim[8] = { 6, 4, 4, 1, 4, 8, 4, 1 };

	for (int i=0; i<8; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}
}


Player_MatchMan::~Player_MatchMan(void)
{
}
