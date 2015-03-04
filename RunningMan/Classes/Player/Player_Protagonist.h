#ifndef __Player_Protagonist_H__
#define __Player_Protagonist_H__

#include "cocos2d.h"
#include <string.h>
#include "Player/Player.h"

class Player_Protagonist : public Player
{
public:
	Player_Protagonist(int id);
	~Player_Protagonist(void);
};

#endif //__Player_Protagonist_H__