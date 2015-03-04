#ifndef __Trap_Coffin_H__
#define __Trap_Coffin_H__

#include "cocos2d.h"
#include "Trap/TrapBase.h"

class TrapCoffin : public TrapBase
{
public:
	TrapCoffin(void);
	~TrapCoffin(void);

	void update(float dt);

	bool checkCollision();
};

#endif //__Trap_Coffin_H__
