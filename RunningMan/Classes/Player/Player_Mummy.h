#ifndef __Player_Mummyt_H__
#define __Player_Mummyt_H__

#include "cocos2d.h"
#include <string.h>
#include "Player/Player.h"

class Player_Mummy : public Player
{
public:
	Player_Mummy(int id);
	~Player_Mummy(void);

public:
	bool m_bUseCoffin;

	void useCoffin();

	void checkCoffinHP();

	void removeCoffin();

private:
	int CoffinHP;
};

#endif //__Player_Mummyt_H__