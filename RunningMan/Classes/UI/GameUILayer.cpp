#include "GameUILayer.h"

#include "Scene/GameScene.h"
#include "Level/GameLevel.h"
#include "Scene/Track.h"

#include "Level/LevelManager.h"
#include "Sound/SoundManager.h"

#include "ResDef.h"

int GameUILayer::LayerTag = 8;
const float GameUILayer::DefaultLevelTime = 300.00f;

const int GameUILayer::PowerNumIconsMax = 4;

bool GameUILayer::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	LevelTime = DefaultLevelTime;

	m_pGameScene = nullptr;
	m_PlayerA = nullptr;
	m_PlayerB = nullptr;

	winSize = cocos2d::Director::getInstance()->getWinSize();

	//----------------
	cocos2d::Vec2 skill_A_icon_pos = cocos2d::Vec2(150,winSize.height - 77);
	cocos2d::Vec2 skill_B_icon_pos = cocos2d::Vec2(748,winSize.height - 77);
	//PowerNumIconsA = new List<CCSprite>(4);
	//PowerNumIconsB = new List<CCSprite>(4);

	for (int i = 0; i < PowerNumIconsMax;++i)
	{
		std::stringstream ss;
		ss<<i; 
		std::string iStr = ss.str();
		std::string textureName = "power_" + iStr + ".png";
		cocos2d::Sprite* spr1 = cocos2d::Sprite::createWithSpriteFrameName(textureName);
		cocos2d::Sprite* spr2 = cocos2d::Sprite::createWithSpriteFrameName(textureName);
		PowerNumIconsA.pushBack(spr1);
		PowerNumIconsB.pushBack(spr2);
		//
		spr1->setVisible(false);
		spr2->setVisible(false);
		//

		this->addChild(spr1, 1);
		this->addChild(spr2, 1);
		//ResDef.g_GUIBatchNode.addChild(spr1, 1);
		//ResDef.g_GUIBatchNode.addChild(spr2, 1);
		//
		spr1->setPosition(skill_A_icon_pos);
		spr2->setPosition(skill_B_icon_pos);

		//
		PowerBarA = cocos2d::Sprite::createWithSpriteFrameName("power_bar.png");
		PowerBarB = cocos2d::Sprite::createWithSpriteFrameName("power_bar.png");
		PowerBarA->setAnchorPoint(cocos2d::Vec2(0, 1.0f));
		PowerBarB->setAnchorPoint(cocos2d::Vec2(0, 1.0f));
		PowerBarA->setPosition(cocos2d::Vec2(18, winSize.height - 44));
		PowerBarB->setPosition(cocos2d::Vec2(616, winSize.height - 44));
		this->addChild(PowerBarA, 5);
		this->addChild(PowerBarB, 5);
		//ResDef.g_GUIBatchNode.addChild(PowerBarA, 5);
		//ResDef.g_GUIBatchNode.addChild(PowerBarB, 5);


		ProgressMaskA = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("images//mask.png"));
		ProgressMaskA->setPosition(skill_A_icon_pos);
		addChild(ProgressMaskA, 3);
		ProgressMaskB = cocos2d::ProgressTimer::create(cocos2d::Sprite::create("images//mask.png"));
		ProgressMaskB->setPosition(skill_B_icon_pos);
		addChild(ProgressMaskB, 3);
		//
		GameOver_label = (cocos2d::Sprite::create("images//Statistics_label.png"));
		GameOver_label->setPosition(winSize.width / 2, winSize.height / 2);
		GameOver_label->setScale(0.01f);
		GameOver_label->setVisible(false);
		addChild(GameOver_label, 109);
		//

		pGameLabel = cocos2d::Label::createWithBMFont("fonts/moto_f.fnt","");
		pGameLabelScoreA = cocos2d::Label::createWithBMFont("fonts/moto_f.fnt","");
		pGameLabelScoreB = cocos2d::Label::createWithBMFont("fonts/moto_f.fnt","");

		pGameLabel->setString("0");
		pGameLabel->setPosition(cocos2d::Vec2(winSize.width / 2, winSize.height / 2));
		addChild(pGameLabel, 100);

		pGameLabelScoreA->setString("");
		pGameLabelScoreB->setString("");

		pGameLabelScoreA->setPosition(cocos2d::Vec2(winSize.width / 2-20, winSize.height / 2));
		pGameLabelScoreB->setPosition(cocos2d::Vec2(winSize.width / 2+20, winSize.height / 2));
		pGameLabelScoreA->setRotation(90.0f);
		pGameLabelScoreB->setRotation(270.0f);

		addChild(pGameLabelScoreA, 101);
		addChild(pGameLabelScoreB, 101);

		pGameLabelScoreA->setVisible(false);
		pGameLabelScoreB->setVisible(false);
		//---------------------------------------------------------------
		cocos2d::Sprite* spCtrl_N = cocos2d::Sprite::createWithSpriteFrameName("replay_normal.png");
		cocos2d::Sprite* spCtrl_S = cocos2d::Sprite::createWithSpriteFrameName("replay_hover.png");
		cocos2d::Sprite* spCtrl_N_2 = cocos2d::Sprite::createWithSpriteFrameName("goto_normal.png");
		cocos2d::Sprite* spCtrl_S_2 = cocos2d::Sprite::createWithSpriteFrameName("goto_hover.png");

		replayBtn = cocos2d::MenuItemSprite::create(
			spCtrl_N, 
			spCtrl_S, 
			nullptr, 
			CC_CALLBACK_1(GameUILayer::callback_OnPressReplay, this));

		gotoSceneMapBtn = cocos2d::MenuItemSprite::create(
			spCtrl_N_2, 
			spCtrl_S_2, 
			nullptr, 
			CC_CALLBACK_1(GameUILayer::callback_OnPressGoOn, this));

		cocos2d::Menu* preplaymenu = cocos2d::Menu::createWithItem(replayBtn);
		preplaymenu->setPosition( cocos2d::Vec2(winSize.width / 2 - 100, winSize.height/2 - 50) );
		addChild(preplaymenu,110);

		cocos2d::Menu* pgotoScenemenu = cocos2d::Menu::createWithItem(gotoSceneMapBtn);
		pgotoScenemenu->setPosition(  cocos2d::Vec2(winSize.width / 2 + 100, winSize.height/2 - 50));
		addChild(pgotoScenemenu,110);
		//
		replayBtn->setVisible(false);
		replayBtn->setEnabled(false);
		gotoSceneMapBtn->setVisible(false);
		gotoSceneMapBtn->setEnabled(false);
	}

	return true;
}

void GameUILayer::update(float dt)
{
	if (m_pGameScene == nullptr )
	{
		return;
	}
	GameLevel* lData = m_pGameScene->GetCurrentLevelData();
	if (lData!= nullptr)
	{
		switch(lData->getRule())
		{
		case LevelRule::RULE_COLLECT_COIN:
			{
				pGameLabel->setVisible(GameScene::UseAI);
				pGameLabelScoreA->setVisible(!GameScene::UseAI);
				pGameLabelScoreB->setVisible(!GameScene::UseAI);

				std::stringstream ss;
				ss<<m_pGameScene->m_PlayerA->GetCollectCoin(); 
				std::string coinAStr = ss.str();

				ss<<m_pGameScene->m_PlayerB->GetCollectCoin();
				std::string coinBStr = ss.str();

				std::string str = "Your Coins: " + 
					coinAStr + 
					"\nCPU's Coins: " + 
					coinBStr;
				pGameLabel->setString(str);
				//
				std::string str_1 = "Your Coins: " + m_pGameScene->m_PlayerA->GetCollectCoin();
				std::string str_2 = "Your Coins: " + m_pGameScene->m_PlayerB->GetCollectCoin();

				pGameLabelScoreA->setString(str_1);
				pGameLabelScoreB->setString(str_2);


			}
			break;
		case LevelRule::RULE_CAREFULLY_TRAP:
			{
				pGameLabel->setString("Carefully run");
			}
			break;
		case LevelRule::RULE_COLLECT_ALLCOIN:
			{
				if (m_PlayerA->iswin() || m_PlayerB->iswin())
				{
					pGameLabel->setVisible(GameScene::UseAI);
					pGameLabelScoreA->setVisible(GameScene::UseAI);
					pGameLabelScoreB->setVisible(GameScene::UseAI);

					std::stringstream ss;
					ss<<m_pGameScene->m_PlayerA->GetCollectCoin(); 
					std::string coinAStr = ss.str();
					
					ss<<m_pGameScene->m_PlayerB->GetCollectCoin();
					std::string coinBStr = ss.str();

					std::string str = "Your Coins: " + coinAStr
						+ "\nCPU's Coins: " + coinBStr;

					pGameLabel->setString(str);
					//
					std::string str_1 = "Your Coins: " + coinAStr;
					std::string str_2 = "Your Coins: " + coinBStr;
					pGameLabelScoreA->setString(str_1);
					pGameLabelScoreB->setString(str_2);
				}
				else
				{
					int n = m_pGameScene->m_Track->getAppearCoin();
					std::stringstream ss;
					ss<<n;
					std::string nStr = ss.str();
					
					pGameLabel->setString(nStr + " Coins Left.");
				}
			}
			break;
		case LevelRule::RULE_OVER_LAPS:
			{
				pGameLabel->setString("3 loop ahead!");
			}
			break;
		case LevelRule::RULE_CATCH_RIVALS:
			{
				pGameLabel->setString("Catch him!");
			}
			break;

		}
	}

	//

	{
		if (IsShowEndLabel == false && m_pGameScene->ShowLabel)
		{
			//
			PlayLabelFrame();
			//

			IsShowEndLabel = true;
		}
	}

	Layer::update(dt);
}

void GameUILayer::restart()
{
	stopAllActions();
	//
	GameOver_label->setVisible(false);
	GameOver_label->stopAllActions();
	replayBtn->setVisible(false);
	replayBtn->setEnabled(false);
	gotoSceneMapBtn->setVisible(false);
	gotoSceneMapBtn->setEnabled(false);
	IsShowEndLabel = false;

	//
	pGameLabel->setVisible(true);
	pGameLabelScoreA->setVisible(false);
	pGameLabelScoreB->setVisible(false);
	//
	m_PlayerA = nullptr;
	m_PlayerB = nullptr;
	ProgressMaskA->stopAllActions();
	ProgressMaskA->setPercentage(0);
	ProgressMaskB->stopAllActions();
	ProgressMaskB->setPercentage(0);
	//

	int playerpower = 0;
	if (GameScene::g_GameMode == RunGameMode::MODE_PVC ||
		GameScene::g_GameMode == RunGameMode::MODE_PVP)
	{
		GameLevel* ldata = LevelManager::Instance()->VsAreaData->m_GameLevels[0];
		if (ldata != nullptr)
		{
			ldata->MatchRestart();

			if (ldata->getRule() == LevelRule::RULE_CAREFULLY_TRAP)
			{
				playerpower = 3;
			}
		}
	}
	else if (GameScene::g_GameMode == RunGameMode::MODE_STORY)
	{
		int curscene = ResDef::getInstance()->g_ConfigStruct.CurrentArea - 1;
		int curlevel = ResDef::getInstance()->g_ConfigStruct.CurrentLevel - 1;
		GameLevel* ldata = LevelManager::Instance()->m_Areas[curscene]->m_GameLevels[curlevel];
		if (ldata != nullptr)
		{
			ldata->MatchRestart();

			if (ldata->getRule() == LevelRule::RULE_CAREFULLY_TRAP)
			{
				playerpower = 3;
			}
		}
	}
	setPlayerA_Power(playerpower);
	setPlayerB_Power(playerpower);
}

void GameUILayer::onEnter()
{
	Layer::onEnter();

	GameScene* MyScene = nullptr;

	cocos2d::Scene* pRunningScene = cocos2d::Director::getInstance()->getRunningScene();
	if (pRunningScene != nullptr)
	{
		Node* pLayer = pRunningScene->getChildByTag(GameScene::LayerTag);
		GameScene* MyScene = (GameScene*)pLayer;
		if (MyScene != nullptr)
		{
			m_PlayerA = MyScene->m_PlayerA;
			m_PlayerB = MyScene->m_PlayerB;
			MyScene->ShowLabel = false;

			//
			m_numPlayer = MyScene->GetPlayerNum();

			//--------------
			if (m_PlayerA != nullptr && m_PlayerB != nullptr)
			{
				setPlayerA_Power(m_PlayerA->GetPower());
				if (ProgressMaskA->isRunning() == false &&
					m_PlayerA->GetPower()!= m_PlayerA->m_MaxPower)
				{
					OnProgressA(m_PlayerA->m_PowerUpTime);
				}
				//
				setPlayerB_Power(m_PlayerB->GetPower());
				if (ProgressMaskB->isRunning() == false &&
					m_PlayerB->GetPower() != m_PlayerB->m_MaxPower)
				{
					OnProgressB(m_PlayerB->m_PowerUpTime);
				}
			}
			jump_menu = nullptr;
			action_menu = nullptr;
			jump_text = nullptr;
			action_text = nullptr;
			jump_menu2 = nullptr;
			action_menu2 = nullptr;
			jump_text2 = nullptr;
			action_text2 = nullptr;
			jumpBtn = nullptr;
			jumpBtn2 = nullptr;
			actionBtn = nullptr;
			actionBtn2 = nullptr;

			//
			if (m_numPlayer == 1)
			{
				jump_text = cocos2d::Sprite::createWithSpriteFrameName("jump_text.png");
				action_text = cocos2d::Sprite::createWithSpriteFrameName("action_text.png");

				cocos2d::Sprite* spCtrl_N = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_normal.png");
				cocos2d::Sprite* spCtrl_S = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_hover.png");
				cocos2d::Sprite* spCtrl_N_2 = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_normal.png");
				cocos2d::Sprite* spCtrl_S_2 = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_hover.png");

				jumpBtn = cocos2d::MenuItemSprite::create(
					spCtrl_N, 
					spCtrl_S, 
					nullptr, 
					CC_CALLBACK_1(GameUILayer::callback_OnPressJumpA, this));

				actionBtn = cocos2d::MenuItemSprite::create(
					spCtrl_N, 
					spCtrl_S, 
					nullptr, 
					CC_CALLBACK_1(GameUILayer::callback_OnPressActionA, this));

				jump_text->setPosition( cocos2d::Vec2(726, winSize.height - 405) );
				action_text->setPosition( cocos2d::Vec2(78, winSize.height - 405) );

				jump_menu = cocos2d::Menu::createWithItem(jumpBtn);
				jump_menu->setPosition( cocos2d::Vec2(726, winSize.height - 405) );
				addChild(jump_menu, 1);
				action_menu = cocos2d::Menu::createWithItem(actionBtn);
				action_menu->setPosition( cocos2d::Vec2(78, winSize.height - 405) );
				addChild(action_menu, 1);

				addChild(jump_text, 5);
				addChild(action_text, 5);
			}
			else
			{
				//先初始化PlayerA

				jump_text = cocos2d::Sprite::createWithSpriteFrameName("jump_text.png");
				action_text = cocos2d::Sprite::createWithSpriteFrameName("action_text.png");

				cocos2d::Sprite* spCtrl_N = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_normal.png");
				cocos2d::Sprite* spCtrl_S = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_hover.png");
				cocos2d::Sprite* spCtrl_N_2 = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_normal.png");
				cocos2d::Sprite* spCtrl_S_2 = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_hover.png");

				jumpBtn = cocos2d::MenuItemSprite::create(
					spCtrl_N, 
					spCtrl_S, 
					nullptr, 
					CC_CALLBACK_1(GameUILayer::callback_OnPressJumpA, this));

				actionBtn = cocos2d::MenuItemSprite::create(
					spCtrl_N_2, 
					spCtrl_S_2, 
					nullptr, 
					CC_CALLBACK_1(GameUILayer::callback_OnPressActionA, this));

				jump_text->setPosition( cocos2d::Vec2(78, winSize.height - 405) );
				action_text->setPosition( cocos2d::Vec2(78, winSize.height - 205) );

				jump_menu = cocos2d::Menu::createWithItem(jumpBtn);
				jump_menu->setPosition( cocos2d::Vec2(78, winSize.height - 405) );
				jump_menu->setRotation(90.0f);
				addChild(jump_menu, 1);
				action_menu = cocos2d::Menu::createWithItem(actionBtn);
				action_menu->setPosition( cocos2d::Vec2(78, winSize.height - 205) );
				action_menu->setRotation(90.0f);
				addChild(action_menu, 1);

				addChild(jump_text, 5);
				addChild(action_text, 5);

				//PlayerB
				jump_text2 = cocos2d::Sprite::createWithSpriteFrameName("jump_text.png");
				action_text2 = cocos2d::Sprite::createWithSpriteFrameName("action_text.png");

				cocos2d::Sprite* spCtrl_N2 = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_normal.png");
				cocos2d::Sprite* spCtrl_S2 = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_hover.png");
				cocos2d::Sprite* spCtrl_N_22 = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_normal.png");
				cocos2d::Sprite* spCtrl_S_22 = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_hover.png");

				jumpBtn = cocos2d::MenuItemSprite::create(
					spCtrl_N2, 
					spCtrl_S2, 
					nullptr, 
					CC_CALLBACK_1(GameUILayer::callback_OnPressJumpB, this));

				actionBtn = cocos2d::MenuItemSprite::create(
					spCtrl_N_22, 
					spCtrl_S_22, 
					nullptr, 
					CC_CALLBACK_1(GameUILayer::callback_OnPressActionB, this));

				jump_text2->setPosition( cocos2d::Vec2(726, winSize.height - 205) );
				action_text2->setPosition( cocos2d::Vec2(726, winSize.height - 405) );

				jump_menu2 = cocos2d::Menu::createWithItem(jumpBtn);
				jump_menu2->setPosition( cocos2d::Vec2(726, winSize.height - 205) );
				jump_menu2->setRotation(270.0f);
				addChild(jump_menu2, 1);
				action_menu2 = cocos2d::Menu::createWithItem(actionBtn);
				action_menu2->setPosition( cocos2d::Vec2(726, winSize.height - 405) );
				action_menu2->setRotation(270.0f);
				addChild(action_menu2, 1);

				addChild(jump_text2, 5);
				addChild(action_text2, 5);
		}
	}

	
	}
	//
	scheduleUpdate();
}

void GameUILayer::onExit()
{
	removeChild(jump_menu,true);
	removeChild(action_menu, true);
	removeChild(jump_text, true);
	removeChild(action_text, true);
	removeChild(jump_menu2, true);
	removeChild(action_menu2, true);
	removeChild(jump_text2, true);
	removeChild(action_text2, true);

	unscheduleUpdate();
	Layer::onExit();
}

void GameUILayer::initPlayerAUI()
{
	
}

void GameUILayer::initPlayerBUI()
{
	jump_text = cocos2d::Sprite::createWithSpriteFrameName("jump_text.png");
	action_text = cocos2d::Sprite::createWithSpriteFrameName("action_text.png");

	cocos2d::Sprite* spCtrl_N = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_normal.png");
	cocos2d::Sprite* spCtrl_S = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_hover.png");
	cocos2d::Sprite* spCtrl_N_2 = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_normal.png");
	cocos2d::Sprite* spCtrl_S_2 = cocos2d::Sprite::createWithSpriteFrameName("ctrl_btn_hover.png");

	jumpBtn = cocos2d::MenuItemSprite::create(
		spCtrl_N, 
		spCtrl_S, 
		nullptr, 
		CC_CALLBACK_1(GameUILayer::callback_OnPressJumpB, this));

	actionBtn = cocos2d::MenuItemSprite::create(
		spCtrl_N_2, 
		spCtrl_S_2, 
		nullptr, 
		CC_CALLBACK_1(GameUILayer::callback_OnPressActionB, this));

	jump_text->setPosition( cocos2d::Vec2(726, winSize.height - 405) );
	jump_text->setPosition( cocos2d::Vec2(78, winSize.height - 405) );

	jump_menu = cocos2d::Menu::createWithItem(jumpBtn);
	jump_text->setPosition( cocos2d::Vec2(726, winSize.height - 405) );
	addChild(jump_menu, 1);
	action_menu = cocos2d::Menu::createWithItem(actionBtn);
	jump_text->setPosition( cocos2d::Vec2(78, winSize.height - 405) );
	addChild(action_menu, 1);

	addChild(jump_text, 5);
	addChild(action_text, 5);
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

void GameUILayer::callback_OnPressReplay(Ref* sender)
{
	replayBtn->setVisible(false);
	replayBtn->setEnabled(false);
	gotoSceneMapBtn->setVisible(false);
	gotoSceneMapBtn->setEnabled(false);
	//
	GameOver_label->setScale(0.01f);
	GameOver_label->setVisible(false);
	IsShowEndLabel = false;
	if (m_pGameScene != nullptr)
	{
		m_pGameScene->ShowLabel = false;
	}	
	//
	int playerpower = 0;

	StopProgress_A();
	StopProgress_B();

	if (GameScene::g_GameMode == RunGameMode::MODE_PVC ||
		GameScene::g_GameMode == RunGameMode::MODE_PVP)
	{
		GameLevel* ldata = LevelManager::Instance()->VsAreaData->m_GameLevels[0];
		if (ldata != nullptr)
		{
			ldata->MatchRestart();

			if (ldata->getRule() == LevelRule::RULE_CAREFULLY_TRAP)
			{
				playerpower = 3;
			}
		}
	}
	else if (GameScene::g_GameMode == RunGameMode::MODE_STORY)
	{
		int curscene = ResDef::getInstance()->g_ConfigStruct.CurrentArea - 1;
		int curlevel = ResDef::getInstance()->g_ConfigStruct.CurrentLevel - 1;
		GameLevel* ldata = LevelManager::Instance()->m_Areas[curscene]->m_GameLevels[curlevel];
		if (ldata != nullptr)
		{
			ldata->MatchRestart();

			if (ldata->getRule() == LevelRule::RULE_CAREFULLY_TRAP)
			{
				playerpower = 3;
			}
		}
	}

	if (m_pGameScene != nullptr)
	{
		m_pGameScene->restart();

		m_PlayerA = m_pGameScene->m_PlayerA;
		m_PlayerB = m_pGameScene->m_PlayerB;
	}
	

	if (GameScene::g_GameMode == RunGameMode::MODE_PVC ||
		GameScene::g_GameMode == RunGameMode::MODE_PVP)
	{
		//SimpleAudioEngine.sharedEngine().playBackgroundMusic(ResDef.g_BackgroundMusic, true);
		SoundManager::Instance()->Play(ResDef::g_BackgroundMusic);
	}
	else
	{
		int curscene = ResDef::getInstance()->g_ConfigStruct.CurrentArea - 1;
		int curlevel = ResDef::getInstance()->g_ConfigStruct.CurrentLevel - 1;
		GameLevel* ldata = LevelManager::Instance()->m_Areas[curscene]->m_GameLevels[curlevel];
		if (ldata != nullptr)
		{
			if (ldata->isBoss())
			{
				//SimpleAudioEngine.sharedEngine().playBackgroundMusic(ResDef.g_BossFightMusic, true);
				SoundManager::Instance()->Play(ResDef::g_BossFightMusic);
			}
			else
			{
				//SimpleAudioEngine.sharedEngine().playBackgroundMusic(ResDef.g_BackgroundMusic, true);
				SoundManager::Instance()->Play(ResDef::g_BackgroundMusic);
			}
		}
	}

	//
	setPlayerA_Power(playerpower);
	setPlayerB_Power(playerpower);
	//
	if (playerpower != 3)
	{
		OnProgressA(m_PlayerA->m_PowerUpTime);
		OnProgressB(m_PlayerB->m_PowerUpTime);
	}
}

void GameUILayer::callback_OnPressGoOn(Ref* sender)
{
	;
}

void GameUILayer::PlayLabelFrame()
{
	GameOver_label->setScale(0.01f);
	GameOver_label->setVisible(true);

	cocos2d::ScaleTo* pSAct= cocos2d::ScaleTo::create(1.0f,1.0f);
	cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(GameUILayer::callback_EndPlayedLabelFrame,this));

	cocos2d::Sequence* pSec = cocos2d::Sequence::createWithTwoActions(pSAct,pCallFunc);
}

void GameUILayer::callback_EndPlayedLabelFrame()
{
	replayBtn->setVisible(true);
	replayBtn->setEnabled(true);
	//只有AI模式，才是单机模式，才可以继续游戏                  
	if (GameScene::g_GameMode == RunGameMode::MODE_STORY )
	{
		if (m_pGameScene != nullptr)
		{
			if (m_pGameScene->m_PlayerA->iswin())
			{
				gotoSceneMapBtn->setVisible(true);
				gotoSceneMapBtn->setEnabled(true);
			}
		}
	}
}

void GameUILayer::callback_ProgressFinish_A(Ref* sender)
{
	if(m_PlayerA != nullptr && m_PlayerA->GetPower() < PowerNumIconsMax)
	{
		m_PlayerA->PowerUp();

		setPlayerA_Power(m_PlayerA->GetPower());

		if (m_PlayerA->GetPower() != m_PlayerA->m_MaxPower)
		{
			OnProgressA(m_PlayerA->m_PowerUpTime);
		}
		else { StopProgress_A(); }
	}
}

void GameUILayer::callback_ProgressFinish_B(Ref* sender)
{
	if (m_PlayerB != nullptr && m_PlayerB->GetPower() < PowerNumIconsMax)
	{
		m_PlayerB->PowerUp();

		setPlayerB_Power(m_PlayerB->GetPower());

		if (m_PlayerB->GetPower() != m_PlayerB->m_MaxPower)
		{
			OnProgressB(m_PlayerB->m_PowerUpTime);
		}
		else { StopProgress_B(); }
	}
}


void GameUILayer::callback_OnPressJumpA(Ref* sender)
{
	m_PlayerA->useJump();
}

void GameUILayer::callback_OnPressActionA(Ref* sender)
{
	m_PlayerA->useSkill();
}

void GameUILayer::callback_OnPressJumpB(Ref* sender)
{
	m_PlayerB->useJump();
}

void GameUILayer::callback_OnPressActionB(Ref* sender)
{
	m_PlayerB->useSkill();
}

void GameUILayer::SetPlayerA(Player* pPlayer)
{
	m_PlayerA = pPlayer;
}

Player* GameUILayer::GetPlayerA()
{
	return m_PlayerA;
}

void GameUILayer::SetPlayerB(Player* pPlayer)
{
	m_PlayerB = pPlayer;
}

Player* GameUILayer::GetPlayerB()
{
	return m_PlayerB;
}


void GameUILayer::StopProgress_A()
{
	ProgressMaskA->setReverseProgress(true);
	//ProgressMaskA-> = 0.0f;
}
void GameUILayer::StopProgress_B()
{
	ProgressMaskB->setReverseProgress(true);
	//ProgressMaskB->Percentage = 0.0f;
}