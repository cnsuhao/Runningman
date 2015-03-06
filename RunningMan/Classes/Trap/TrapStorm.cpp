#include "TrapStorm.h"

USING_NS_CC;

TrapStorm::TrapStorm(void)
{
	m_TrapType = TrapType::TRAP_STORM;
	m_FrameBaseName = "Storm";
	m_TotalFrames = 4;
}


TrapStorm::~TrapStorm(void)
{
}

void TrapStorm::update(float dt)
{
	TrapBase::update(dt);
}

bool TrapStorm::checkCollision()
{
	return false;
}

void TrapStorm::setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy)
{
	this->setPosition(playerpos);

	anchopos.y += 65;

	if (width > 0.0f && height > 0.0f)
	{
		anchopos.y = anchopos.y - height/2.0f;
		float ax = 0.5f - (rotateBy.x - anchopos.x) / width;
		float ay = 0.5f - (rotateBy.y - anchopos.y) / height;
		this->setAnchorPoint(Vec2(ax, ay));
	}
	else
	{
		//ÓÐÎÊÌâ;
	}

	this->setRotation(rot);
}