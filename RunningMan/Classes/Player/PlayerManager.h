#ifndef __Player_Manager_H__
#define __Player_Manager_H__

#include "Player/Player.h"
#include "Player/Player_MatchMan.h"
#include "Player/Player_Mummy.h"
#include "Player/Player_Pharaoh.h"
#include "Player/Player_Protagonist.h"

class PlayerManager
{
private:
	static PlayerManager* m_Instance;
public:
	PlayerManager(void);
	~PlayerManager(void);

	Player* CreatePlayer(GameRoleType roleIndex,int playerID);

	static PlayerManager* Instance();

	void Reset();

	Player* GetPlayerA();

	Player* GetPlayerB();

private:
	Player* m_PlayerA;
	Player* m_PlayerB;
};

#endif //__Player_Manager_H__
