#include "PlayerManager.h"

#include "Player/Player_Protagonist.h"
#include "Player/Player_Pharaoh.h"
#include "Player/Player_Mummy.h"
#include "Player/Player_MatchMan.h"


PlayerManager* PlayerManager::m_Instance = nullptr;

PlayerManager* PlayerManager::Instance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new PlayerManager();
	}

	return m_Instance;
}

PlayerManager::PlayerManager(void)
{
	m_PlayerA = nullptr;
	m_PlayerB = nullptr;
}


PlayerManager::~PlayerManager(void)
{
}

Player* PlayerManager::CreatePlayer(GameRoleType roleIndex,int playerID)
{
	Player* player = nullptr;
	//
	switch (roleIndex)
	{
	case GameRoleType::GameRoleType_ARSEHOLE:
		player = new Player_Protagonist(playerID);
		break;
		//
	case GameRoleType::GameRoleType_PHARAOH:
		player = new Player_Pharaoh(playerID);
		break;
		//
	case GameRoleType::GameRoleType_MUMMY:
		player = new Player_Mummy(playerID);
		break;
		//
	case GameRoleType::GameRoleType_MATCHMAN:
		player = new Player_MatchMan(playerID);
		break;
	}
	if (player != nullptr)
	{
		//player->userData = roleIndex;

		player->SetResource();

		if (playerID == 1)
		{
			m_PlayerA = player;
		}
		else if (playerID == 2)
		{
			m_PlayerB = player;
		}
	}
	//
	return player;
}

Player* PlayerManager::GetPlayerA()
{
	return m_PlayerA;
}

Player* PlayerManager::GetPlayerB()
{
	return m_PlayerB;
}

void PlayerManager::Reset()
{
	m_PlayerA = nullptr;
	m_PlayerB = nullptr;
}