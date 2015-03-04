#include "ProjectileBase.h"

#include "Player/PlayerManager.h"

ProjectileBase::ProjectileBase(void)
{
	m_RunAV = 0.0f;
	m_CurRunAV = 4.0f;
	m_TotalRunAngle = 0.0f;

	m_OffsetHeight = 0.0f;

	m_IsAlive = true;

	std::string test[10] = {"fly"};
	ActionsName = test; 
}


ProjectileBase::~ProjectileBase(void)
{
}

bool ProjectileBase::isAlive()
{
	return m_IsAlive;
}

void ProjectileBase::setRunAngularVelocity(float v)
{
	m_RunAV = v;
}

float ProjectileBase::getTotalRunAngle()
{
	return m_TotalRunAngle;
}

void ProjectileBase::update(float dt)
{
	if (m_IsAlive == false)
	{
		return;
	}

	float currot = this->getRotation();
	this->setRotation(currot + m_CurRunAV);

	if (this->getRotation() > 360.0f)
	{
		this->setRotation(this->getRotation() - 360.0f);
	}
	else if (this->getRotation() < -360.0f)
	{
		this->setRotation(this->getRotation() + 360.0f);
	}

	if (m_CurRunAV > 0.0f)
	{
		m_TotalRunAngle += m_CurRunAV;
	}
	else if (m_CurRunAV < 0.0f)
	{
		m_TotalRunAngle -= m_CurRunAV;
	}

	m_LifeTime--;
	if (m_LifeTime<=0)
	{
		m_IsAlive = false;
	}
}

bool ProjectileBase::checkProjectileAttactPlayer(Player* pplayer)
{
	float projtileAngle = this->getRotation();
	float playerAngle = pplayer->getRotation();
	if (projtileAngle<0.0f)
	{
		projtileAngle += 360.0f;
	}
	if (playerAngle < 0.0f)
	{
		playerAngle += 360.0f;
	}
	if (projtileAngle < (playerAngle + 10.0f) &&
		projtileAngle > (playerAngle - 10.0f))
	{
		return true;
	}

	return false;
}

void ProjectileBase::setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy)
{
	this->setPosition(playerpos);

	if (width > 0.0f && height > 0.0f)
	{
		float ax = 0.5f - (rotateBy.x - anchopos.x) / width;
		float ay = 0.5f - (rotateBy.y - anchopos.y) / height;
		this->setAnchorPoint(cocos2d::Vec2(ax, ay));
		m_SavedOldAncho = this->getAnchorPoint();
		m_OldSavedPos = anchopos;
		m_SavedRotateBy = rotateBy;
	}
	else
	{
		//ÓÐÎÊÌâ;
	}

	this->setRotation(rot);
	m_OriginalRotation = rot;
}