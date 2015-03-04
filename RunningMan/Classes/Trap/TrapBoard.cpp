#include "TrapBoard.h"

USING_NS_CC;

TrapBoard::TrapBoard(void)
{
	m_TrapType = TrapType::TRAP_BOARD;
	m_FrameBaseName = "careful";
	m_TotalFrames = 1;
}


TrapBoard::~TrapBoard(void)
{
}

void TrapBoard::setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy)
{
	this->setPosition(playerpos);

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

void TrapBoard::update(float dt)
{
	TrapBase::update(dt);
}

bool TrapBoard::checkCollision()
{
	return false;
}