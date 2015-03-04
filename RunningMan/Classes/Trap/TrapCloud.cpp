#include "TrapCloud.h"

USING_NS_CC;

TrapCloud::TrapCloud(void)
{
	m_TrapType = TrapType::TRAP_CLOUD;
	m_FrameBaseName = "cloud";
	m_TotalFrames = 0;

	//----------------------------------
	m_SafeFrameBase = "cloud";
	m_TotalDangerFrames = 3;
	//----------------------------------
	m_DangerFrameBase = "cloud";
	m_TotalDangerFrames = 5;
	//----------------------------------
}


TrapCloud::~TrapCloud(void)
{
}

void TrapCloud::update(float dt)
{
	TrapBase::update(dt);
}

bool TrapCloud::checkCollision()
{
	return false;
}

void TrapCloud::setDangerAndSafeResource()
{
	std::string suffixStr = ".png";

	m_DangerAnimFrames.clear();

	for(int i=0; i<m_TotalDangerFrames; ++i)
	{
		std::stringstream ss;
		ss<<i; 
		std::string indexStr = ss.str();
		std::string namestr = m_DangerFrameBase + "_" + indexStr + suffixStr;
		cocos2d::SpriteFrame*pSpriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(namestr);
		m_DangerAnimFrames.pushBack(pSpriteframe);
	}

	m_SafeAnimFrames.clear();

	for(int i=0; i<m_TotalSafeFrames; ++i)
	{
		std::stringstream ss;
		ss<<i; 
		std::string indexStr = ss.str();
		std::string namestr = m_SafeFrameBase + "_" + indexStr + suffixStr;
		cocos2d::SpriteFrame*pSpriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(namestr);
		m_SafeAnimFrames.pushBack(pSpriteframe);
	}
}

void TrapCloud::PlayTrapAnimation()
{
	playSafeAnimation();
}

void TrapCloud::playSafeAnimation()
{
	m_bUsingTrap = false;

	cocos2d::Vector<FiniteTimeAction*> pAcs;

	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(m_SafeAnimFrames);

	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);
	animaction->setDuration(2.0f);
	pAcs.pushBack(animaction);

	cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(TrapCloud::callbackSafe,this));
	pAcs.pushBack(pCallFunc);

	Sequence* pSec = Sequence::create(pAcs);

	this->runAction(pSec);
}

void TrapCloud::playDangerAnimation()
{
	m_bUsingTrap = false;

	cocos2d::Vector<FiniteTimeAction*> pAcs;

	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(m_DangerAnimFrames);

	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);
	animaction->setDuration(2.0f);
	pAcs.pushBack(animaction);

	cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(TrapCloud::callbackDanger,this));
	pAcs.pushBack(pCallFunc);

	Sequence* pSec = Sequence::create(pAcs);

	this->runAction(pSec);
}

void TrapCloud::callbackSafe()
{
	playDangerAnimation();
}

void TrapCloud::callbackDanger()
{
	playSafeAnimation();
}

void TrapCloud::setRotateByPoint(cocos2d::Vec2 playerpos, cocos2d::Vec2 anchopos, float rot, cocos2d::Vec2 rotateBy)
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