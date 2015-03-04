#ifndef __Trap_Storm_H__
#define __Trap_Storm_H__

#include "cocos2d.h"
#include "Trap/TrapBase.h"

class TrapStorm : public TrapBase
{
public:
	TrapStorm(void);
	~TrapStorm(void);

	void update(float dt);

	bool checkCollision();

	void setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy);
};

#endif //__Trap_Storm_H__
