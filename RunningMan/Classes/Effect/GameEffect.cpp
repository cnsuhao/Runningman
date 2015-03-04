#include "GameEffect.h"

const std::string GameEffect::effectTextureName = "effect";

int GameEffect::s_Index = 0;

GameEffect::GameEffect(float alivetime, bool bLoop, float onceTime) :
	cocos2d::Sprite()
{
	m_AliveTime = alivetime;
	m_bAlive = true;
	m_bLoop = bLoop;
	m_fOnceTime = onceTime;
	m_FrameName = "";
	m_Action = nullptr;
	m_Index = s_Index++;
	//
	Playing = false;
}


GameEffect::~GameEffect(void)
{
}

void GameEffect::Init()
{
	cocos2d::Vector<cocos2d::SpriteFrame*> temp ;

	for (int k = 0; k < m_FrameCount; ++k)
	{
		std::stringstream ss;
		ss<<k; 
		std::string kStr = ss.str();

		std::string finalframeName = effectTextureName + "_" + m_FrameName + "_" + kStr + ".png";
		cocos2d::SpriteFrame* spriteframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(finalframeName);
		if (spriteframe != nullptr)
		{
			temp.pushBack(spriteframe);
		}
	}

	std::string initName = effectTextureName + "_" + m_FrameName + "_0.png";
	cocos2d::SpriteFrame* defaultframe = cocos2d::SpriteFrameCache::getInstance()->getSpriteFrameByName(initName);
	this->initWithSpriteFrame(defaultframe);
	this->setAnchorPoint(cocos2d::Vec2(0.5f, 0.5f));
	cocos2d::Animation* ani = cocos2d::Animation::createWithSpriteFrames(temp,m_fOnceTime / m_FrameCount);
	cocos2d::Animate* animaction = cocos2d::Animate::create(ani);

	if (m_bLoop)
	{
		m_Action = cocos2d::RepeatForever::create(animaction);
	}
	else
	{
		m_Action = animaction;

	}
}

void GameEffect::update(float delta)
{
	Sprite::update(delta);

	if (m_AliveTime > 0.0f)
	{
		m_AliveTime -= delta;
	}
	else
	{
		m_bAlive = false;
	}
}

void GameEffect::Play()
{
	if (m_Action != nullptr && Playing == false)
	{
		this->runAction(m_Action);
		Playing = true;

	}
}

void GameEffect::Stop()
{
	if (m_Action != nullptr && Playing == true)
	{
		this->stopAction(m_Action);
		Playing = false;
	}
}

bool GameEffect::getAlive()
{
	return m_bAlive;
}

int GameEffect::getIndex()
{
	return m_Index;
}