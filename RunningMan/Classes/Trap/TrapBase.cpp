#include "TrapBase.h"


TrapBase::TrapBase(void)
{
}


TrapBase::~TrapBase(void)
{
}

void TrapBase::setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy)
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

void TrapBase::update(float dt)
{
	cocos2d::Sprite::update(dt);
}

void TrapBase::SetResource()
{
	m_AnimFrames.clear();

	std::string suffixStr = ".png";

	cocos2d::SpriteFrame* pSpriteframe = nullptr;

	if(m_TotalFrames == 0)
	{
		return;
	}
	if(m_TotalFrames == 1)
	{
		pSpriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(m_FrameBaseName + suffixStr);
		m_AnimFrames.pushBack(pSpriteframe);

		initWithSpriteFrameName(m_FrameBaseName + suffixStr);
	}
	else
	{
		for(int i=0; i<m_TotalFrames; ++i)
		{
			std::stringstream ss;
			ss<<i; 
			std::string indexStr = ss.str();
			std::string namestr = m_FrameBaseName + "_" + indexStr + suffixStr;
			pSpriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(namestr);
			m_AnimFrames.pushBack(pSpriteframe);
		}


		std::stringstream ss;
		ss<<0; 
		std::string indexStr = ss.str();
		std::string namestr = m_FrameBaseName + "_" + indexStr + suffixStr;

		initWithSpriteFrameName(namestr);
	}
	
	this->width = pSpriteframe->getRect().size.width;
	height = pSpriteframe->getRect().size.height;
}

void TrapBase::PlayTrapAnimation()
{
	playAnimation();
}

void TrapBase::playAnimation()
{
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(m_AnimFrames);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);
	animaction->setDuration(1.0f);

	cocos2d::RepeatForever* pRepeat = cocos2d::RepeatForever::create(animaction);

	this->runAction(pRepeat);
}