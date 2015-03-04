#include "Player_Pharaoh.h"
#include "Skill/SkillManager.h"


Player_Pharaoh::Player_Pharaoh(int id) :
	Player(id)
{
	m_RoleType = "Role_Pharaoh";
	//Skill
	m_PlayerSkill_Run = SkillManager::Instance()->CreateSkill(SkillType::SKILL_BOARD, this);

	m_PlayerSkill_Jump = SkillManager::Instance()->CreateSkill(SkillType::SKILL_BANANA, this);

	m_PlayerSkill_Fall = SkillManager::Instance()->CreateSkill(SkillType::SKILL_ANGER, this);

	m_matchManTextureName = "Pharaoh";


	int frameanim[8] = { 6, 4, 4, 1, 4, 8, 4, 1 };
	
	for (int i=0; i<8; ++i)
	{
		m_ActionsFrameCount.push_back(cocos2d::Value(frameanim[i]));
	}
}


Player_Pharaoh::~Player_Pharaoh(void)
{
}
