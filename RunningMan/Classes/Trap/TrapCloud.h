#ifndef __Trap_Cloud_H__
#define __Trap_Cloud_H__

#include "cocos2d.h"
#include "Trap/TrapBase.h"

class TrapCloud : public TrapBase
{
public:
	TrapCloud(void);
	~TrapCloud(void);

	void update(float dt);

	bool checkCollision();

	void PlayTrapAnimation();

	void setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy);

private:
	void playSafeAnimation();
	void playDangerAnimation();
	void callbackSafe();
	void callbackDanger();

	void setDangerAndSafeResource();

	cocos2d::Vector<cocos2d::SpriteFrame*> m_DangerAnimFrames;
	cocos2d::Vector<cocos2d::SpriteFrame*> m_SafeAnimFrames;
	std::string m_DangerFrameBase;
	int m_TotalDangerFrames;
	std::string m_SafeFrameBase;
	int m_TotalSafeFrames;
};

#endif //__Trap_Cloud_H__
