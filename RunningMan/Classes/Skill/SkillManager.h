#ifndef __SKILL_MGR_H__
#define __SKILL_MGR_H__

#include "cocos2d.h"

enum SkillType
{
	SKILL_BANANA = 0,
	SKILL_BOARD,
	SKILL_ANGER,
	SKILL_SPEEDMAX,
	SKILL_FLY,
	SKILL_POWERUPTURBO,
	SKILL_WAND,
	SKILL_USECOFFIN,
	SKILL_COFFINTHROW,
	SKILL_SUPERANGER,
	SKILL_WEAKFLY,
	SKILL_NULL,
};

class SkillBase;
class Player;

class SkillManager
{
private:
	static SkillManager* m_Instance;
public:
	SkillManager(void);
	~SkillManager(void);

	static SkillManager* Instance();

	SkillBase* CreateSkill(SkillType type, Player* pPlayer);
};

#endif //__SKILL_MGR_H__