#include "WorldMapScene.h"
#include "Level/LevelManager.h"
#include "Sound/SoundManager.h"
#include "ResDef.h"
#include "UI/LogoUI.h"
#include "UI/HelpUI.h"
#include "UI/GameUILayer.h"
#include "Scene/GameScene.h"

USING_NS_CC;

const float WorldMapScene::touchRadius = 20.0f;

Scene* WorldMapScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = WorldMapScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

WorldMapScene::WorldMapScene(void)
{
}


WorldMapScene::~WorldMapScene(void)
{
}

bool WorldMapScene::init()
{
	cocos2d::Menu* pMenu = nullptr;
	//////////////////////////////
	currentSelectLevel = -1;
	this->setTouchEnabled(true);
	winSize = cocos2d::Director::getInstance()->getWinSize();

	cocos2d::Sprite* spr_Back_normal = cocos2d::Sprite::create("ctrl_btn_normal.png");
	cocos2d::Sprite* spr_Back_hover = cocos2d::Sprite::create("ctrl_btn_hover.png");
	cocos2d::Sprite* spr_Start_normal = cocos2d::Sprite::create("ctrl_btn_normal.png");
	cocos2d::Sprite* spr_Start_hover = cocos2d::Sprite::create("ctrl_btn_hover.png");


	cocos2d::MenuItemSprite* button_Back = cocos2d::MenuItemSprite::create(
		spr_Back_normal,
		spr_Back_hover,
		this,
		CC_CALLBACK_1(WorldMapScene::callback_OnPressBack, this)
		);
	cocos2d::MenuItemSprite* button_Start = cocos2d::MenuItemSprite::create(
		spr_Start_normal,
		spr_Start_hover,
		this,
		CC_CALLBACK_1(WorldMapScene::callback_OnPressStart, this)
		);

	pMenu = cocos2d::Menu::createWithItem(button_Back);
	pMenu->setPosition(cocos2d::Vec2(78, winSize.height - 405));
	this->addChild(pMenu, 1);
	//
	pMenu = cocos2d::Menu::createWithItem(button_Start);
	pMenu->setPosition(cocos2d::Vec2(726, winSize.height - 405));
	this->addChild(pMenu, 1);
	//
	cocos2d::Sprite* spBack = cocos2d::Sprite::createWithSpriteFrameName("back_text.png");
	cocos2d::Sprite* spStart = cocos2d::Sprite::createWithSpriteFrameName("start_text.png");
	spBack->setPosition(78, winSize.height - 405);
	spStart->setPosition(726, winSize.height - 405);
	//
	this->addChild(spBack,5);
	this->addChild(spStart,5);
	//map
	SetCurrentScene(SceneIndex);
	//
	return true;
}

void WorldMapScene::SetCurrentScene(int nS)
{
	SceneIndex = nS;
	//
	if (m_pMap != nullptr)
	{
		removeChild(m_pMap,true);
	}
	if (m_crossesIcons.size() != 0)
	{
		for (int i=0; i<m_crossesIcons.size(); ++i)
		{
			removeChild(m_crossesIcons.at(i),true);
		}

		m_crossesIcons.clear();
	}
	if (m_circleIcons.size() != 0)
	{
		for (int i=0; i<m_circleIcons.size(); ++i)
		{
			removeChild(m_circleIcons.at(i),true);
		}
		m_circleIcons.clear();
	}
	//
	if (nS < ResDef::getInstance()->g_ConfigStruct.CurrentArea)
	{
		//PassedLevel = DateDef.SceneDataPool[nS - 1].LevelNum;
	}
	else if (nS == ResDef::getInstance()->g_ConfigStruct.CurrentArea)
	{
		if (ResDef::getInstance()->g_ConfigStruct.MaxShowLevel == 0)
		{
			ResDef::getInstance()->g_ConfigStruct.MaxShowLevel = 1;
		}
		PassedLevel = ResDef::getInstance()->g_ConfigStruct.MaxShowLevel;
	}
	else
	{
		PassedLevel = 0;
	}
	//因为要遍历，从0开始~~
	nS = nS - 1;
	if (nS < 0) return;
	//
	std::stringstream ss;
	ss<<nS;
	std::string nsStr = ss.str();
	m_pMap = Sprite::create(ResDef::g_WorldMapNameBase + nsStr);
	m_pMap->setPosition(Vec2(winSize.width / 2.0f, winSize.height / 2.0f));

	addChild(m_pMap, 0);

	m_crossesIcons.clear();
	m_circleIcons.clear();

	//m_crossesIcons = new List<CCSprite>(DateDef.SceneDataPool[nS].LevelNum);
	//m_circleIcons = new List<CCSprite>(DateDef.SceneDataPool[nS].LevelNum);
	for (int i = 0; i < LevelManager::Instance()->m_Areas[nS]->LevelNum; ++i)
	{
		Sprite* pCross = Sprite::create("cross.png");
		Sprite* pCircle = Sprite::create("circle.png");
		//
		if (i < PassedLevel)
		{
			pCircle->setVisible(true);
			pCross->setVisible(false);
		}
		else
		{
			pCircle->setVisible(false);
			pCross->setVisible(true);
		}
		//
		m_crossesIcons.pushBack(pCross);
		m_circleIcons.pushBack(pCircle);
	}
	//

	int index = 0;
	for (int i=0; i<m_crossesIcons.size(); ++i)
	{
		GameLevel* ldata = LevelManager::Instance()->m_Areas[nS]->GetGameLevel(index++);
		Sprite* spr = m_crossesIcons.at(i);
		if (spr != nullptr)
		{
			spr->setPosition(ldata->levelPoint);
			addChild(spr, 3);
			removeChild(m_crossesIcons.at(i),true);
		}		
	}

	for (int i=0; i<m_circleIcons.size(); ++i)
	{
		GameLevel* ldata = LevelManager::Instance()->m_Areas[nS]->GetGameLevel(index++);
		Sprite* spr = m_circleIcons.at(i);
		if (spr != nullptr)
		{
			spr->setPosition(ldata->levelPoint);
			addChild(spr, 3);
			removeChild(m_circleIcons.at(i),true);
		}		
	}
}

void WorldMapScene::update(float dt)
{

}

void WorldMapScene::onEnter()
{
	;
}
void WorldMapScene::onExit()
{
	;
}

//callback
void WorldMapScene::callback_OnPressBack(Ref* sender)
{
	SoundManager::Instance()->PlayEffect(ResDef::g_PowerDownSound);
	cocos2d::Director::getInstance()->replaceScene(LogoUI::createScene());
}
void WorldMapScene::callback_OnPressStart(Ref* sender)
{
	SoundManager::Instance()->PlayEffect(ResDef::g_SelectSound);
	if (currentSelectLevel != -1)
	{
		if (currentSelectLevel+1 > PassedLevel)
		{
			currentSelectLevel = -1;
			return;
		}
		ResDef::getInstance()->g_ConfigStruct.CurrentLevel = currentSelectLevel + 1;
		//测试用的场景1

		cocos2d::Scene* pGame_Scene = GameScene::createScene(ResDef::getInstance()->g_ConfigStruct.CurrentArea);

		cocos2d::Director::getInstance()->replaceScene(pGame_Scene);

		Node* pLayer = pGame_Scene->getChildByTag(GameScene::LayerTag);
		GameScene* pGameLayer = (GameScene*)pLayer;
		if (pGameLayer != nullptr)
		{
			pGameLayer->restart();
		}

		Node* pUILayer = pGame_Scene->getChildByTag(GameUILayer::LayerTag);
		GameUILayer* pGameUILayer = (GameUILayer*)pUILayer;
		if (pGameUILayer != nullptr)
		{
			pGameUILayer->restart();
		}

		//
		if (ResDef::getInstance()->g_ConfigStruct.NeedPlayHelp)
		{
			ResDef::getInstance()->g_ConfigStruct.NeedPlayHelp = 0;
			CCDirector::getInstance()->pushScene(HelpUI::createScene());
		}
		currentSelectLevel = -1;
	}
	else
	{
		ResDef::getInstance()->g_ConfigStruct.CurrentLevel = ResDef::getInstance()->g_ConfigStruct.MaxShowLevel;
		//测试用的场景1
		cocos2d::Scene* pGame_Scene = GameScene::createScene(ResDef::getInstance()->g_ConfigStruct.CurrentArea);
		cocos2d::Director::getInstance()->replaceScene(pGame_Scene);

		Node* pLayer = pGame_Scene->getChildByTag(GameScene::LayerTag);
		GameScene* pGameLayer = (GameScene*)pLayer;
		if (pGameLayer != nullptr)
		{
			pGameLayer->restart();
		}

		Node* pUILayer = pGame_Scene->getChildByTag(GameUILayer::LayerTag);
		GameUILayer* pGameUILayer = (GameUILayer*)pUILayer;
		if (pGameUILayer != nullptr)
		{
			pGameUILayer->restart();
		}

		//
		if (ResDef::getInstance()->g_ConfigStruct.NeedPlayHelp)
		{
			ResDef::getInstance()->g_ConfigStruct.NeedPlayHelp = 0;
			CCDirector::getInstance()->pushScene(HelpUI::createScene());
		}
	}
}