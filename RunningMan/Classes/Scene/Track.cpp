#include "Track.h"

#include "Trap/TrapManager.h"
#include "Trap/TrapBase.h"

#include "Item/ItemManager.h"
#include "Item/ItemBase.h"

const int Track::NumTrapPoint = 360;

Track::Track(void)
{
	MaxDegree = CC_DEGREES_TO_RADIANS(360.0f);

	m_OffsetTrapAngle = 4.0f; 
}


Track::~Track(void)
{
}

void Track::restart()
{
	m_AppearCoin = 0;

	this->removeAllChildrenWithCleanup(true);

	TrapManager::Instance()->CleanTraps();

	ItemManager::Instance()->CleanItems();

	//TrapManager::Instance()->CleanTraps();

	//TrapManager::Instance()->CleanTraps();

	//TrapManager::Instance()->CleanTraps();
}

void Track::destoryAllTrackObject()
{
	TrapManager::Instance()->DestoryAll();
}

void Track::InitTrackData(cocos2d::Vec2 center, float r)
{
	//初始化数据
	m_TrackCenter = center;
	m_radius = r;

	//计算每个陷阱放置点的位置
	float everyAngle = 360.0f / (float)NumTrapPoint;
	float trapangel = 0.0f;
	m_TrapPointList.push_back(cocos2d::Value(trapangel));
	for (int index = 1; index < NumTrapPoint; ++index)
	{
		trapangel += everyAngle;
		m_TrapPointList.push_back(cocos2d::Value(trapangel));
	}
}

void Track::update(float dt)
{
	TrapManager::Instance()->update(dt);

	ItemManager::Instance()->update(dt);

	//Projectile Check

	//clear del list
}

float Track::getTrapAngle(int index)
{
	if (index < NumTrapPoint)
	{
		return m_TrapPointList.at(index).asFloat();
	}
	return 0.0f;
}

TrapBase* Track::getTrap(float angle)
{
	if (angle < 0.0f)
	{
		angle = angle + 360.0f;
	}
	int index = (int)(angle * 100.0f / 360.0f);

	if (index < NumTrapPoint)
	{
		return TrapManager::Instance()->GetTrap(index);
	}
	return nullptr;
}

void Track::CreateTrap(float angle, TrapType type)
{
	if (angle<0.0f)
	{
		angle = 360 + angle;
	}
	angle += m_OffsetTrapAngle;
	if (angle > 360.0f)
	{
		angle -= 360.0f;
	}
	int index = (int)(angle * 100.0f / 360.0f);
	if (index==100)
	{
		index = 0;
	}

	TrapBase* pTrap = TrapManager::Instance()->CreateTrap(index,type);
	if (pTrap != nullptr)
	{
		cocos2d::Vec2 anchoPos = cocos2d::Vec2(m_TrackCenter.x, m_TrackCenter.y - m_radius);
		pTrap->setRotateByPoint(m_TrackCenter, anchoPos, angle, m_TrackCenter);
		addChild(pTrap,0);
	}
}

bool Track::checkTrap(float angle)
{
	if (angle < 0.0f)
	{
		angle = angle + 360.0f;
	}
	int index = (int)(angle * 100.0f / 360.0f);

	return TrapManager::Instance()->CheckTrap(index);	
}

int Track::numActiveTrap()
{
	return TrapManager::Instance()->GetNumActiveTraps();
}

void Track::delTrap(float angle)
{
	if (angle < 0.0f)
	{
		angle = angle + 360.0f;
	}
	int index = (int)(angle * 100.0f / 360.0f);

	auto pTrap = TrapManager::Instance()->GetTrap(index);

	if (pTrap != nullptr)
	{
		pTrap->removeFromParentAndCleanup(true);

		TrapManager::Instance()->delTrap(index);
	}
}

//item
ItemBase* Track::getItem(float angle)
{
	if (angle < 0.0f)
	{
		angle = angle + 360.0f;
	}
	int index = (int)(angle * 100.0f / 360.0f);

	if (index < NumTrapPoint)
	{
		return ItemManager::Instance()->GetItem(index);
	}
	return nullptr;
}

void Track::CreateItem(float angle, ItemType type)
{
	if (angle < 0.0f)
	{
		angle = 360 + angle;
	}

	if (angle > 360.0f)
	{
		angle -= 360.0f;
	}
	int index = (int)(angle * 100.0f / 360.0f);
	if (index == 100)
	{
		index = 0;
	}

	ItemBase* pItem = ItemManager::Instance()->CreateItem(index,type);
	if (pItem != nullptr)
	{
		cocos2d::Vec2 anchoPos = cocos2d::Vec2(m_TrackCenter.x, m_TrackCenter.y - m_radius);
		pItem->setRotateByPoint(m_TrackCenter, anchoPos, angle, m_TrackCenter);
		addChild(pItem,0);
	}
}

bool Track::checkItem(float angle)
{
	if (angle < 0.0f)
	{
		angle = angle + 360.0f;
	}
	int index = (int)(angle * 100.0f / 360.0f);

	return ItemManager::Instance()->CheckItem(index);	
}

void Track::delItem(float angle)
{
	if (angle < 0.0f)
	{
		angle = angle + 360.0f;
	}
	int index = (int)(angle * 100.0f / 360.0f);

	ItemBase* pItem = ItemManager::Instance()->GetItem(index);
	if (pItem != nullptr)
	{
		removeChild(pItem,true);
		ItemManager::Instance()->DelItem(index);	
	}	
}

//Projectile
ProjectileBase* Track::CreateProjectile(ProjectileType type, float angle)
{
	return nullptr;
}

bool Track::checkProjectile(float angle)
{
	return false;
}

//Coin
void Track::deleteDeadCoin()
{
	;
}

void Track::collectedCoin(){
	;
}

int Track::getAppearCoin(){
	return m_AppearCoin;
}

void Track::CreateCoinEdge(){
	;
}

void Track::CreateAllCoin(){
	;
}

void Track::gamePause(){;}

void Track::gameResume(){;}