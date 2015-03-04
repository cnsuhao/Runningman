#ifndef __Trap_RedCactus_H__
#define __Trap_RedCactus_H__

#include "cocos2d.h"
#include "Trap/TrapBase.h"

class TrapRedCactus : public TrapBase
{
public:
	TrapRedCactus(void);
	~TrapRedCactus(void);

	void update(float dt);

	bool checkCollision();

	void PlayTrapAnimation();

	void setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy);

private:
	void callbackReady();

	void setReadyResource();

	cocos2d::Vector<cocos2d::SpriteFrame*> m_ReadyAnimFrames;
	std::string m_ReadyFrameBase;
	int m_TotalReadyFrames;
};

#endif //__Trap_RedCactus_H__
