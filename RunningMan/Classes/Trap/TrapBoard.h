#ifndef __Trap_Board_H__
#define __Trap_Board_H__

#include "cocos2d.h"
#include "Trap/TrapBase.h"

class TrapBoard : public TrapBase
{
public:
	TrapBoard(void);
	~TrapBoard(void);

	void playAnimation();

	void update(float dt);

	bool checkCollision();

	void setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy);
};

#endif //__Trap_Board_H__
