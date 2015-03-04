#include "HelpUI.h"
#include "Sound/SoundManager.h"
#include "ResDef.h"

NS_CC_BEGIN

const int HelpUI::HelpPicsNum = 2;

HelpUI::HelpUI(void)
{
	currentHelpPage = 0;
}


HelpUI::~HelpUI(void)
{
}

cocos2d::Scene* HelpUI::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = HelpUI::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool HelpUI::init()
{
	for (int i = 1; i <= HelpPicsNum; ++i)
	{
		std::stringstream ss;
		ss<<i; 
		std::string iStr = ss.str();

		std::string fileName = ResDef::g_HelpUIImage + iStr;
		Sprite* spr = Sprite::create(fileName);
		if (spr != nullptr)
		{
			m_HelpPics.pushBack(spr);
		}
	}
	//
	Size winSize = Director::getInstance()->getWinSize();
	for (int i=0; i<m_HelpPics.size(); ++i)
	{
		Sprite* sprPic = m_HelpPics.at(i);
		sprPic->setPosition(winSize.width / 2, winSize.height / 2);
		sprPic->setVisible(false);
		this->addChild(sprPic,0);
	}

	Sprite* curHelp = m_HelpPics.at(currentHelpPage);

	curHelp->setVisible(true);
	//
	Sprite* spNext_N = Sprite::createWithSpriteFrameName("next_btn_normal.png");
	Sprite* spNext_S = Sprite::createWithSpriteFrameName("next_btn_hover.png");
	Sprite* spSkip_N = Sprite::createWithSpriteFrameName("skip_btn_normal.png");
	Sprite* spSkip_S = Sprite::createWithSpriteFrameName("skip_btn_hover.png");
	//
	pNextItem = MenuItemSprite::create(
		spNext_N, spNext_S, this, CC_CALLBACK_1(HelpUI::callback_NextPage,this));
	pSkipItem = MenuItemSprite::create(
		spSkip_N, spSkip_S, this, CC_CALLBACK_1(HelpUI::callback_OnSkip,this));

	next_menu = Menu::createWithItem(pNextItem);
	next_menu->setPosition(540, winSize.height - 445);
	this->addChild(next_menu, 1);
	skip_menu = Menu::createWithItem(pSkipItem);
	skip_menu->setPosition(265, winSize.height - 445);
	this->addChild(skip_menu, 20);
	//

	//
	return true;
}
void HelpUI::update(float dt)
{
	;
}

void HelpUI::onEnter()
{
	SoundManager::Instance()->Play(ResDef::g_SceneMapMusic);

	ScaleTo* sst = ScaleTo::create(1, 1.3f);
	ScaleTo* sst_back = ScaleTo::create(1, 1.0f);
	Sequence* sseq = Sequence::createWithTwoActions(sst, sst_back);
	RepeatForever* sact = RepeatForever::create(sseq);

	//pSkipItem.runAction(sact);
	//
	ScaleTo* st = ScaleTo::create(1,1.3f);
	ScaleTo* st_back = ScaleTo::create(1, 1.0f);
	Sequence* seq =Sequence::createWithTwoActions(st,st_back);
	RepeatForever* act = RepeatForever::create(seq);

	//pNextItem.runAction(act);


	//
	//GameStatusManager.instance.SetStatus(GameStatus.GAMESTATUS_HELP);
}
void HelpUI::onExit()
{
	pNextItem->stopAllActions();
	pSkipItem->stopAllActions();
	//
	Layer::onExit();
}


void HelpUI::callback_NextPage(Ref* sender)
{
	int oldPage = currentHelpPage;
	currentHelpPage++;
	{
		m_HelpPics.at(oldPage)->setVisible(false);
		m_HelpPics.at(currentHelpPage)->setVisible(true);
	}
	if (currentHelpPage == HelpPicsNum - 1)
	{
		pNextItem->setEnabled(false);
		pNextItem->setVisible(false);
	}
}
void HelpUI::callback_OnSkip(Ref* sender)
{
	CCDirector::getInstance()->popScene();
}

NS_CC_END