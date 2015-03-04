#ifndef __SKILL_BASE_H__
#define __SKILL_BASE_H__

#include "cocos2d.h"

class Player;
class SkillBase
{
public:
	SkillBase(Player* pPlayer);
	~SkillBase(void);

	virtual void useSkill();

	int getConsume();

protected:
	Player* m_pPlayer;

	int m_SkillConsume;
};

#endif //__SKILL_BASE_H__