#include "TrapRedCactus.h"

USING_NS_CC;

TrapRedCactus::TrapRedCactus(void)
{
	m_TrapType = TrapType::TRAP_REDCACTUS;
	m_FrameBaseName = "Cactus";
	m_TotalFrames = 1;

	//-----------------------------
	m_ReadyFrameBase = "Cactus";
	m_TotalReadyFrames = 4;
	//-----------------------------
	setReadyResource();
}

TrapRedCactus::~TrapRedCactus(void)
{
}

void TrapRedCactus::update(float dt)
{
	TrapBase::update(dt);
}

bool TrapRedCactus::checkCollision()
{
	return false;
}
//-------------------------------------------------------
void TrapRedCactus::setReadyResource()
{
	std::string suffixStr = ".png";

	m_ReadyAnimFrames.clear();

	for(int i=0; i<m_TotalReadyFrames; ++i)
	{
		std::stringstream ss;
		ss<<i; 
		std::string indexStr = ss.str();
		std::string namestr = m_ReadyFrameBase + "_" + indexStr + suffixStr;
		cocos2d::SpriteFrame*pSpriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(namestr);
		m_ReadyAnimFrames.pushBack(pSpriteframe);
	}
}

void TrapRedCactus::PlayTrapAnimation()
{
	m_bUsingTrap = false;

	cocos2d::Vector<FiniteTimeAction*> pAcs;

	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(m_ReadyAnimFrames,1.0f);

	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);
	animaction->setDuration(2.0f);
	pAcs.pushBack(animaction);

	cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(TrapRedCactus::callbackReady,this));
	pAcs.pushBack(pCallFunc);

	Sequence* pSec = Sequence::create(pAcs);

	this->runAction(pSec);
}

void TrapRedCactus::callbackReady()
{
	playAnimation();
}

void TrapRedCactus::setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy)
{
	this->setPosition(playerpos);

	anchopos.y += 2.2f;

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