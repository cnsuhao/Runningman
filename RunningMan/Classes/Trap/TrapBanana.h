#ifndef __Trap_Banana_H__
#define __Trap_Banana_H__

#include "cocos2d.h"
#include "Trap/TrapBase.h"

class TrapBanana : public TrapBase
{
public:
	TrapBanana(void);
	~TrapBanana(void);

	void update(float dt);

	bool checkCollision();
};

#endif //__Trap_Banana_H__
