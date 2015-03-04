#ifndef __SKILL_BOARD_H__
#define __SKILL_BOARD_H__

#include "cocos2d.h"
#include "Skill/SkillBase.h"

class SkillBoard : public SkillBase
{
public:
	SkillBoard(Player* pPlayer);
	~SkillBoard(void);

	virtual void useSkill();

protected:
};

#endif //__SKILL_BOARD_H__