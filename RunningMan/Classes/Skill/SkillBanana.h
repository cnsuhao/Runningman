#ifndef __SKILL_BANANA_H__
#define __SKILL_BANANA_H__

#include "cocos2d.h"
#include "Skill/SkillBase.h"

class SkillBanana : public SkillBase
{
public:
	SkillBanana(Player* pPlayer);
	~SkillBanana(void);

	virtual void useSkill();

protected:
};

#endif //__SKILL_BANANA_H__