#include "ItemBase.h"


ItemBase::ItemBase(void)
{
	//this->Opacity = 0;
}


ItemBase::~ItemBase(void)
{
}

void ItemBase::setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy)
{
	this->setPosition(playerpos);

	if (width > 0.0f && height > 0.0f)
	{
		float ax = 0.5f - (rotateBy.x - anchopos.x) / width;
		float ay = 0.5f - (rotateBy.y - anchopos.y) / height;
		this->setAnchorPoint(cocos2d::Vec2(ax, ay));
	}
	else
	{
		//ÓÐÎÊÌâ;
	}

	this->setRotation(rot);
}

void ItemBase::update(float dt)
{
	Sprite::update(dt);
}

bool ItemBase::checkCollision()
{
	return false;
}

ItemType ItemBase::getItemType()
{
	return m_ItemType;
}

void ItemBase::readydead()
{
	m_bUsingItem = false;
}