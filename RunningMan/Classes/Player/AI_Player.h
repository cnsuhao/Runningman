#ifndef __AI_Player_H__
#define __AI_Player_H__

#include "cocos2d.h"
#include <string.h>

#include "Manager\PlayerStatusMgr.h"

class Track;

class AI_Player
{
public:
	AI_Player(Player* pPlayerA,Player* pPlayerB, Track* pTrack);
	~AI_Player(void);

	Player* body;
	Player* enemy;
	Track* road;

	void SetEnable(bool bSet){Enabled = bSet;}
	bool GetEnable(){return Enabled;}

	void update(float dt);
	void restart();
	void clear();

protected:
	//Random rnd;
	bool Enabled;

	float timeCounter;

	int m_AILevel;
	int m_AIMaxLevel;
};

#endif //__AI_Player_H__