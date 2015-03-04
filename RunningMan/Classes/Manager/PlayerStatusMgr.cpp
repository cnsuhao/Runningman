#include "PlayerStatusMgr.h"
#include "Player/Player.h"
#include "Player/PlayerStatus.h"

PlayerStatusMgr::PlayerStatusMgr(Player* pplayer)
{
	m_pPlayer = pplayer;
	m_PlayerStatus = nullptr;
}


PlayerStatusMgr::~PlayerStatusMgr(void)
{
}

void PlayerStatusMgr::SetPlayerStatus(PlayerStatus* status)
{
	if (m_PlayerStatus != nullptr)
	{
		m_PlayerStatus->Exit(m_pPlayer);
	}

	m_PlayerStatus = status;

	m_PlayerStatus->Enter(m_pPlayer);
}

PlayerStatus* PlayerStatusMgr::GetCurPlayerStatus()
{
	return m_PlayerStatus;
}

void PlayerStatusMgr::update(float dt)
{
	if (m_PlayerStatus != nullptr)
	{
		m_PlayerStatus->Execute(m_pPlayer,dt);
	}
}