#include "TrapManager.h"
#include "Trap/TrapBanana.h"
#include "Trap/TrapBoard.h"
#include "Trap/TrapCoffin.h"
#include "Trap/TrapCloud.h"
#include "Trap/TrapRedCactus.h"
#include "Trap/TrapStorm.h"

TrapManager* TrapManager::m_Instance = nullptr;

const int TrapManager::NumTrapPlace = 360;

TrapManager* TrapManager::Instance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new TrapManager();
	}

	return m_Instance;
}

TrapManager::TrapManager(void)
{
}


TrapManager::~TrapManager(void)
{
}

TrapBase* TrapManager::CreateTrap(int index, TrapType type)
{
	if ( m_TrapList.at(index) != nullptr)
	{
		return nullptr;
	}

	TrapBase* pTrap = nullptr;
	switch (type)
	{
		case TrapType::TRAP_BANANA:
			pTrap = new TrapBanana();
			break;
		case TrapType::TRAP_BOARD:
			pTrap = new TrapBoard();
			break;
		case TrapType::TRAP_COFFIN:
			pTrap = new TrapCoffin();
			break;
		case TrapType::TRAP_CLOUD:
			pTrap = new TrapCloud();
			break;
		case TrapType::TRAP_REDCACTUS:
			pTrap = new TrapRedCactus();
			break;
		case TrapType::TRAP_STORM:
			pTrap = new TrapStorm();
			break;                   
		break;
	}

	if (pTrap != nullptr)
	{
		pTrap->SetResource();
		pTrap->PlayTrapAnimation();
		//m_TrapList.replace(index,pTrap);
		m_TrapList.insert(index,pTrap);
	}
	return pTrap;
}

void TrapManager::CleanTraps()
{
	//for (int i; i<m_TrapList.size(); ++i)
	//{
	//	TrapBase* pTrap = m_TrapList.at(i);
	//	CC_SAFE_DELETE(pTrap);
	//	m_TrapList.replace(i,nullptr);
	//}

	m_TrapList.clear();
}

void TrapManager::DestoryAll()
{
	CleanTraps();
}

int TrapManager::GetNumActiveTraps()
{
	//int activeTrapCount = 0;

	//for (cocos2d::Map<int,TrapBase*>::iterator it = m_TrapList.begin(); it!=m_TrapList.end(); ++it)
	//{
	//	TrapBase* pTrap = it->second;
	//	if (pTrap != nullptr)
	//	{
	//		activeTrapCount++;
	//	}
	//}

	int activeTrapCount = m_TrapList.size();

	//for (int i = 0; i < m_TrapList.size(); ++i)
	//{
	//	if (m_TrapList.at(i) != nullptr)
	//	{
	//		activeTrapCount++;
	//	}
	//}
	return activeTrapCount;
}

bool TrapManager::CheckTrap(int index)
{
	//if (m_TrapList.at(index) == nullptr)
	//{
	//	return false;
	//}

	cocos2d::Map<int,TrapBase*>::iterator it = m_TrapList.find(index);
	if (it == m_TrapList.end())
	{
		return false;
	}

	return true;
}

void TrapManager::update(float dt)
{
	//for (int i = 0; i < m_TrapList.size(); ++i)
	//{
	//	TrapBase* pTrap = m_TrapList.at(i);
	//	if (pTrap != nullptr)
	//	{
	//		pTrap->update(dt);
	//	}
	//}

	for (cocos2d::Map<int,TrapBase*>::iterator it = m_TrapList.begin(); it!=m_TrapList.end(); ++it)
	{
		TrapBase* pTrap = it->second;
		if (pTrap != nullptr)
		{
			pTrap->update(dt);
		}
	}
}

TrapBase* TrapManager::GetTrap(int index)
{
	//if (index < NumTrapPlace)
	//{
	//	return m_TrapList.at(index);
	//}

	cocos2d::Map<int,TrapBase*>::iterator it = m_TrapList.find(index);
	if (it != m_TrapList.end())
	{
		return it->second;
	}

	return nullptr;
}

void TrapManager::delTrap(int index)
{
	//TrapBase* pTrap = m_TrapList.at(index);
	//if (pTrap != nullptr)
	//{
	//	CC_SAFE_DELETE(pTrap);
	//	m_TrapList.replace(index,nullptr);
	//}

	cocos2d::Map<int,TrapBase*>::iterator it = m_TrapList.find(index);
	if (it != m_TrapList.end())
	{
		m_TrapList.erase(it);
	}
}