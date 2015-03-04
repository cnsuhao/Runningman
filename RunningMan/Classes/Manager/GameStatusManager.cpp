#include "GameStatusManager.h"

GameStatusManager* GameStatusManager::m_Instance = nullptr;

GameStatusManager* GameStatusManager::Instance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new GameStatusManager();
	}

	return m_Instance;
}

GameStatusManager::GameStatusManager(void)
{
}


GameStatusManager::~GameStatusManager(void)
{
}

void GameStatusManager::SetStatus(GameStatus state)
{
	switch (m_CurStatus)
	{
	case GameStatus::GAMESTATUS_TITLE:
		break;
	}

	m_CurStatus = state;

	switch (m_CurStatus)
	{
	case GameStatus::GAMESTATUS_TITLE:
		break;
	}
}

GameStatus GameStatusManager::GetStatus()
{
	return m_CurStatus;
}