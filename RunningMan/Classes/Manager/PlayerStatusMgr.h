#ifndef __PLAYERSTATUS_MANAGER_H__
#define __PLAYERSTATUS_MANAGER_H__

#include "cocos2d.h"

class PlayerStatus;
class Player;

class PlayerStatusMgr
{
public:
	PlayerStatusMgr(Player* pplayer);
	~PlayerStatusMgr(void);	

	void SetPlayerStatus(PlayerStatus* status);

	PlayerStatus* GetCurPlayerStatus();

	void update(float dt);

private:
	PlayerStatus* m_PlayerStatus;

	Player* m_pPlayer;
};

#endif //__PLAYERSTATUS_MANAGER_H__