#ifndef __Trap_Base_H__
#define __Trap_Base_H__

#include "cocos2d.h"

enum TrapType
{
	TRAP_BANANA = 0,
	TRAP_BOARD,
	TRAP_CLOUD,
	TRAP_COFFIN,
	TRAP_REDCACTUS,
	TRAP_STORM,
};


class TrapBase : public cocos2d::Sprite
{
public:
	TrapBase(void);
	~TrapBase(void);

	virtual void setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy);

	void update(float dt);

	virtual bool checkCollision()
	{
		return false;
	}

	TrapType getTrapType()
	{
		return m_TrapType;
	}

	void setWidth(float va){width = va;}
	void setHeight(float va){height = va;}
	float getWidth(){return width;}
	float getHeight(){return height;}

	void SetResource();

	virtual void PlayTrapAnimation();

	bool m_bUsingTrap;

protected:
	TrapType m_TrapType;

	cocos2d::Vector<cocos2d::SpriteFrame*> m_AnimFrames;
	std::string m_FrameBaseName;
	int m_TotalFrames;

	float width;
	float height;

	void playAnimation();
	
};

#endif //__Trap_Base_H__