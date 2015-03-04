#include "GameUILayer.h"

int GameUILayer::LayerTag = 8;
const float GameUILayer::DefaultLevelTime = 300.00f;

bool GameUILayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	LevelTime = DefaultLevelTime;

	winSize = cocos2d::Director::getInstance()->getWinSize();

	pGameLabel = cocos2d::Label::createWithBMFont("fonts/moto_f.fnt","");
	pGameLabelScoreA = cocos2d::Label::createWithBMFont("fonts/moto_f.fnt","");
	pGameLabelScoreB = cocos2d::Label::createWithBMFont("fonts/moto_f.fnt","");

	pGameLabel->setPosition(cocos2d::Vec2(winSize.width / 2, winSize.height / 2));
	pGameLabelScoreA->setPosition(cocos2d::Vec2(winSize.width / 2-20, winSize.height / 2));
	pGameLabelScoreB->setPosition(cocos2d::Vec2(winSize.width / 2+20, winSize.height / 2));

	return true;
}

void GameUILayer::update(float dt)
{
	;
}

void GameUILayer::restart()
{
	;
}

void GameUILayer::onEnter()
{
	;
}

void GameUILayer::onExit()
{
	;
}

void GameUILayer::setPlayerA_Power(int power)
{
	
}

void GameUILayer::setPlayerB_Power(int power)
{
	;
}

void GameUILayer::OnProgressA(float duringTime)
{
	;
}

void GameUILayer::OnProgressB(float duringTime)
{
	;
}

void GameUILayer::callback_OnPressReplay()
{
	;
}

void GameUILayer::callback_OnPressGoOn()
{
	;
}

void GameUILayer::PlayLabelFrame()
{
	;
}

void GameUILayer::callback_EndPlayedLabelFrame()
{
	;
}

void GameUILayer::callback_ProgressFinish_A()
{
	;
}

void GameUILayer::callback_ProgressFinish_B()
{
	;
}


void GameUILayer::callback_OnPressJumpA()
{
	;
}

void GameUILayer::callback_OnPressActionA()
{
	;
}

void GameUILayer::callback_OnPressJumpB()
{
	;
}

void GameUILayer::callback_OnPressActionB()
{
	;
}
