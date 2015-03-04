#ifndef __SKILL_ANGER_H__
#define __SKILL_ANGER_H__

#include "cocos2d.h"
#include "Skill/SkillBase.h"

class SkillAnger : public SkillBase
{
public:
	SkillAnger(Player* pPlayer);
	~SkillAnger(void);

	virtual void useSkill();

protected:
};

#endif //__SKILL_ANGER_H__