#include "GameScene.h"
#include "math/CCMath.h"
#include "UI/GameUILayer.h"
#include "Scene/Track.h"
#include "Level/Area.h"
#include "Level/GameLevel.h"
#include "Player/AI_Player.h"

#include "Level/LevelManager.h"
#include "Sound/SoundManager.h"
#include "Effect/EffectManager.h"
#include "Item/ItemManager.h"

#include "UI/LogoUI.h"
#include "UI/StoryEndUI.h"

#include "ResDef.h"

USING_NS_CC;

RunGameMode GameScene::g_GameMode = RunGameMode::MODE_PVC;

int GameScene::LayerTag = 1;

AI_Player* GameScene::m_AI = nullptr;

bool GameScene::UseAI = false;

Scene* GameScene::createScene(int useSceneID)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
	layer->setSceneID(useSceneID);
	layer->SceneInit();
	auto uilayer = GameUILayer::create();

    // add layer as a child to scene
    scene->addChild(layer,1,GameScene::LayerTag);
	scene->addChild(uilayer,2,GameUILayer::LayerTag);

    // return the scene
    return scene;
}


cocos2d::Node* GameScene::GetNode()
{
	auto scene = cocos2d::Director::sharedDirector()->getRunningScene();
	if (scene != nullptr)
	{
		auto gs = (scene->getChildByTag(GameScene::LayerTag));
		return gs;
	}
	//
	return nullptr;

}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
	//CCDirector::getInstance()->deviceOrientation = ccDeviceOrientation.CCDeviceOrientationLandscapeLeft;

	if ( !Layer::init() )
	{
		return false;
	}
    
    return true;
}

GameScene::GameScene()
{
	m_EveryLevelUpMax = 150;
	m_LevelUpCountdown = m_EveryLevelUpMax;
	m_GameLevel = 0;

	m_NumProjectiles = 50;

	cradius = 170.0f;
	//
	
}

void GameScene::SceneInit()
{
	m_PlayerA = nullptr;
	m_PlayerB = nullptr;
	m_AI = nullptr;

	m_bGameOver = true;
	m_strWinerIs = "";
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	this->setTouchEnabled(true);

	/////////////////////////////
	ShowLabel = false;

	//game init

	Vec2 ccenter = Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f);

	std::stringstream ss;
	ss<<m_SceneIndex; 
	std::string indexStr = ss.str();

	std::string scene_textureName = "images//scene_" + indexStr + ".png";
	std::string bg_textureName = "images//scene_" + indexStr + "_bg" + ".png";

	m_TrackPic = Sprite::create(scene_textureName);
	m_BG = Sprite::create(bg_textureName);
	m_TrackPic->setPosition(Vec2(ccenter.x, ccenter.y));
	m_BG->setPosition(Vec2(ccenter.x, ccenter.y));
	addChild(m_BG, 1);
	addChild(m_TrackPic, 2);

	//CCPoint ccenter = new CCPoint(0.0f, 0.0f);

	//1 track
	m_Track = new Track();
	m_Track->InitTrackData(ccenter, cradius);
	//
	if (g_GameMode == RunGameMode::MODE_STORY)
	{
		int curscene = ResDef::getInstance()->g_ConfigStruct.CurrentArea - 1;
		int curlevel = ResDef::getInstance()->g_ConfigStruct.CurrentLevel - 1;
		GameLevel* ldata = LevelManager::Instance()->m_Areas[curscene]->GetGameLevel(curlevel);
		if (ldata != nullptr)
		{
			SetPlayersType(GameRoleType::GameRoleType_ARSEHOLE, (GameRoleType)(ldata->getEnemyRoleType()));
		}
	}
	InitPlayers();

	//track
	//ResDef::getInstance()->g_GameBatchNode->addChild(m_Track,3);

	//addChild(ResDef::getInstance()->g_GameBatchNode, 3);

	addChild(m_Track, 3);

	//AI proxy playerB!
	m_AI = new AI_Player(m_PlayerB,m_PlayerA, m_Track);
	m_AI->SetEnable(UseAI);

	m_bGameOver = false;

	UseAI = false;

	auto listenerKeyboard = EventListenerKeyboard::create();
	listenerKeyboard->onKeyPressed = CC_CALLBACK_2(GameScene::onKeyPressed, this);
	listenerKeyboard->onKeyReleased = CC_CALLBACK_2(GameScene::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listenerKeyboard, this);
}

void GameScene::onKeyPressed(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
	if (code == cocos2d::EventKeyboard::KeyCode::KEY_Q)
	{
		m_PlayerA->useJump();
	}	
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_W)
	{
		m_PlayerA->useSkill();
	}
}

void GameScene::onKeyReleased(cocos2d::EventKeyboard::KeyCode code, cocos2d::Event* event)
{
}


void GameScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void GameScene::InitPlayers()
{
	//2 player 
	Size screenSize = Director::getInstance()->getVisibleSize();
	Vec2 ccenter = Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f);
	if (m_PlayerA != nullptr)
	{
		//ResDef::getInstance()->g_GameBatchNode->removeChild(m_PlayerA, true);
		m_PlayerA->removeFromParentAndCleanup(true);
	}
	if (m_PlayerB != nullptr)
	{
		//ResDef::getInstance()->g_GameBatchNode->removeChild(m_PlayerB,true);
		m_PlayerB->removeFromParentAndCleanup(true);
	}

	m_PlayerA = PlayerManager::Instance()->CreatePlayer(PlayerAType, 1);
	m_PlayerB = PlayerManager::Instance()->CreatePlayer(PlayerBType, 2);

	Vec2 playerAAnchoPos = Vec2(ccenter.x, ccenter.y - cradius - 10.0f);
	Vec2 playerBAnchoPos = Vec2(ccenter.x, ccenter.y - cradius - 10.0f);

	m_PlayerA->setRunAngularVelocity(-1.0f);
	m_PlayerB->setRunAngularVelocity(-1.0f);

	m_PlayerA->setSpeedUpRunAngularVelocity(-1.5f);
	m_PlayerB->setSpeedUpRunAngularVelocity(-1.5f);

	m_PlayerA->setRotateByPoint(ccenter, playerAAnchoPos, 0.0f, ccenter);
	m_PlayerB->setRotateByPoint(ccenter, playerBAnchoPos, 180.0f, ccenter);

	m_PlayerA->setJumpHeight(32.0f, 1.0f);
	m_PlayerB->setJumpHeight(32.0f, 1.0f);
	//
	//ResDef::getInstance()->g_GameBatchNode->addChild(m_PlayerA, 1);
	//ResDef::getInstance()->g_GameBatchNode->addChild(m_PlayerB, 1);

	addChild(m_PlayerA, 5);
	addChild(m_PlayerB, 5);
	m_PlayerA->setVisible(true);
	//
}

void GameScene::update(float dt)
{
	//1 track
	m_Track->update(dt);
	//2 player
	m_PlayerA->update(dt);
	m_PlayerB->update(dt);
	//--AI-update
	m_AI->update(dt);
	//
	EffectManager::Instance()->update(dt);
	//
	if (m_bGameOver == false)
	{
		//3 是否中了陷阱
		if (m_Track->checkTrap(m_PlayerA->getRotation()) == true)
		{
			TrapBase* ptrap = m_Track->getTrap(m_PlayerA->getRotation());
			if (ptrap != nullptr && ptrap->m_bUsingTrap == true)
			{
				if (m_PlayerA->catchTrap(ptrap->getTrapType()))
				{
					m_Track->delTrap(m_PlayerA->getRotation());
				}
			}
		}
		if (m_Track->checkTrap(m_PlayerB->getRotation()) == true)
		{
			TrapBase* ptrap = m_Track->getTrap(m_PlayerB->getRotation());
			if (ptrap != nullptr && ptrap->m_bUsingTrap == true)
			{
				if (m_PlayerB->catchTrap(ptrap->getTrapType()))
				{
					m_Track->delTrap(m_PlayerB->getRotation());
				}
			}
		}

		//是否吃了物品
		if (m_Track->checkItem(m_PlayerA->getRotation()) == true)
		{
			ItemBase* pitem = m_Track->getItem(m_PlayerA->getRotation());
			if (pitem != nullptr && pitem->m_bUsingItem == true)
			{
				if (m_PlayerA->catchItem(pitem->getItemType()))
				{
					pitem->readydead();
					if (pitem->getItemType() == ItemType::Item_Coin)
					{
						m_Track->collectedCoin();
					}

				}
			}
		}
		if (m_Track->checkItem(m_PlayerB->getRotation()) == true)
		{
			ItemBase* pitem = m_Track->getItem(m_PlayerB->getRotation());
			if (pitem != nullptr && pitem->m_bUsingItem == true)
			{
				if (m_PlayerB->catchItem(pitem->getItemType()))
				{
					pitem->readydead();
					if (pitem->getItemType() == ItemType::Item_Coin)
					{
						m_Track->collectedCoin();
					}
				}
			}
		}

		//-----------------------------------------------------
		//4 胜负检测
		int curscene = ResDef::getInstance()->g_ConfigStruct.CurrentArea - 1;
		int curlevel = ResDef::getInstance()->g_ConfigStruct.CurrentLevel - 1;

		GameLevel* ldata = nullptr;
		if (GameScene::g_GameMode == RunGameMode::MODE_STORY)
		{
			ldata = LevelManager::Instance()->m_Areas[curscene]->GetGameLevel(curlevel);
		}
		else if (GameScene::g_GameMode == RunGameMode::MODE_PVP ||
			GameScene::g_GameMode == RunGameMode::MODE_PVC)
		{
			ldata = LevelManager::Instance()->VsAreaData->GetGameLevel(0);
		}

		if (ldata != nullptr)
		{
			if (ldata->getRule() == LevelRule::RULE_COLLECT_COIN)
			{
				ldata->LimitTimePassed(dt);
			}                    

			if (ldata->IsMatchOver() == true)
			{
				m_bGameOver = true;
				if (m_PlayerA->iswin())
				{                            
					m_strWinerIs = "PlayerA";

					if (GameScene::g_GameMode == RunGameMode::MODE_STORY)
					{
						int maxlevel = LevelManager::Instance()->m_Areas[curscene]->LevelNum;
						if (ResDef::getInstance()->g_ConfigStruct.CurrentLevel >= maxlevel)
						{
							//scene完成
							if ((curscene==0) && (ResDef::getInstance()->IsRoleLocked(2) == true))
							{
								ResDef::getInstance()->UnlockRoleID(2);
								ResDef::getInstance()->SaveConfig();

							}                          

							// 进入通关界面
							if (curscene == LevelManager::SceneNum-1
								&& ResDef::getInstance()->g_ConfigStruct.FinishedEgyptStory == false)
							{

								ResDef::getInstance()->g_ConfigStruct.FinishedEgyptStory = true;
								ResDef::getInstance()->SaveConfig();

								cocos2d::DelayTime* pDelay = cocos2d::DelayTime::create(2);
								cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(GameScene::callbackShowEndStoryUI,this));
								auto seq = Sequence::create( pDelay, pCallFunc, nullptr );
								this->runAction(seq);

								return;
							}
						}
						else if (ResDef::getInstance()->g_ConfigStruct.CurrentLevel == ResDef::getInstance()->g_ConfigStruct.MaxShowLevel)
						{
							ResDef::getInstance()->g_ConfigStruct.MaxShowLevel++;
						}
					}
				}
				else if (m_PlayerB->iswin())
				{
					m_strWinerIs = "PlayerB";
				}
			}
		}


		//5 是否需要生成新的陷阱
		//取游戏时间
		m_LevelUpCountdown--;
		if (m_LevelUpCountdown <= 0)
		{
			m_GameLevel++;
			m_LevelUpCountdown = m_EveryLevelUpMax;

			if (ldata->getRule() != LevelRule::RULE_CAREFULLY_TRAP)
			{
				//int rndtype = rnd.Next(100);
				int rndtype = (int)(CCRANDOM_0_1()*100);
				if (rndtype<=10)
				{
					randomCreateCloud();
				}
				else if (rndtype>10&&rndtype<=70)
				{
					randomCreateRedCactus();
				}
				else if(rndtype>70)
				{
					randomCreateStorm();
				}   
			}
			else
			{
				int rndtype = (int)(CCRANDOM_0_1()*100);
				if (rndtype <= 70)
				{
					randomCreateRedCactus();
				}
				else if (rndtype > 70)
				{
					randomCreateStorm();
				}   
			}

			//6 生成金币
			if (ldata != nullptr && ldata->getRule() == LevelRule::RULE_COLLECT_COIN)
			{
				if (ldata->IsRandomCreateCoin())
				{
					for (int i = 0; i < 10; ++i)
					{
						randomCreateCoin();
					}                            
				}
			}
		}

		//7 删除吃掉的金币
		m_Track->deleteDeadCoin();


		//m_LevelUpCountdown--;
		//if (m_LevelUpCountdown <= 0)
		//{
		//    m_GameLevel++;
		//    m_LevelUpCountdown = m_EveryLevelUpMax;
		//    for (int i = 0; i < 5; ++i )
		//    {
		//        randomCreateCoin();
		//    }

		//}
	}
	else
	{
		cocos2d::Action* act = getActionByTag(1);

		if (act == nullptr && ShowLabel == false)
		{
			ResDef::getInstance()->SaveConfig();
			//////////////////////////////////////////////////////////////////////////
			DelayTime* pDelay = DelayTime::create(3);
			cocos2d::CallFuncN* pCallFunc = cocos2d::CallFuncN::create(CC_CALLBACK_0(GameScene::callbackShowLabel,this));
			auto seq = Sequence::create( pDelay, pCallFunc, nullptr );

			seq->setTag(1);
			this->runAction(seq);
		}

	}
}

void GameScene::restart()
{
	//
	stopAllActions();
	//
	m_bGameOver = false;
	m_strWinerIs = "";
	//
	if (m_Track != nullptr)
	{
		m_Track->restart();

		if (GameScene::g_GameMode == RunGameMode::MODE_PVC ||
			GameScene::g_GameMode == RunGameMode::MODE_PVP)
		{
			GameLevel* ldata = LevelManager::Instance()->VsAreaData->GetGameLevel(0);
			if (ldata != nullptr)
			{
				ldata->MatchRestart();

				int scenetexid = ldata->getSceneMapTexID();

				m_TrackPic->removeFromParentAndCleanup(true);
				m_BG->removeAllChildrenWithCleanup(true);

				std::stringstream ss;
				ss<<scenetexid; 
				std::string indexStr = ss.str();

				std::string scene_textureName = "images//scene_" + indexStr;
				std::string bg_textureName = "images//scene_" + indexStr + "_bg";

				m_TrackPic = Sprite::create(scene_textureName);
				m_BG = Sprite::create(bg_textureName);

				Size screenSize = Director::getInstance()->getWinSize();
				Vec2 ccenter = Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f);
				m_TrackPic->setPosition(Vec2(ccenter.x, ccenter.y));
				m_BG->setPosition(Vec2(ccenter.x, ccenter.y));

				addChild(m_BG, 1);
				addChild(m_TrackPic, 2);

				if (ldata->getRule() == LevelRule::RULE_COLLECT_ALLCOIN)
				{
					createAllCoinEdge();
					createAllCoin();                            
				}
				else if ( ldata->getRule() == LevelRule::RULE_COLLECT_COIN )
				{
					createAllCoinEdge();
					//for (int i = 0; i < ldata.getReadyCreateCoinNum(); ++i)
					//{
					//    randomCreateCoin();
					//}
					createAllCoin(); 
				}
			}   
		}
		else if (GameScene::g_GameMode == RunGameMode::MODE_STORY)
		{
			int curscene = ResDef::getInstance()->g_ConfigStruct.CurrentArea - 1;
			int curlevel = ResDef::getInstance()->g_ConfigStruct.CurrentLevel - 1;
			GameLevel* ldata = LevelManager::Instance()->m_Areas[curscene]->GetGameLevel(curlevel);
			if (ldata != nullptr)
			{
				ldata->MatchRestart();

				int scenetexid = ldata->getSceneMapTexID();

				m_TrackPic->removeFromParentAndCleanup(true);
				m_BG->removeAllChildrenWithCleanup(true);

				std::stringstream ss;
				ss<<scenetexid; 
				std::string indexStr = ss.str();

				std::string scene_textureName = "images//scene_" + indexStr;
				std::string bg_textureName = "images//scene_" + indexStr + "_bg";

				m_TrackPic = Sprite::create(scene_textureName);
				m_BG = Sprite::create(bg_textureName);

				Size screenSize = Director::getInstance()->getVisibleSize();
				Vec2 ccenter = Vec2(screenSize.width / 2.0f, screenSize.height / 2.0f);
				m_TrackPic->setPosition(Vec2(ccenter.x, ccenter.y));
				m_BG->setPosition(Vec2(ccenter.x, ccenter.y));

				addChild(m_BG, 1);
				addChild(m_TrackPic, 2);

				if (ldata->getRule() == LevelRule::RULE_COLLECT_ALLCOIN ||
					ldata->getRule() == LevelRule::RULE_COLLECT_COIN)
				{
					createAllCoinEdge();

					//for (int i = 0; i < ldata.getReadyCreateCoinNum(); ++i)
					//{
					//    randomCreateCoin();
					//}
					createAllCoin(); 
				}
			}   
		}

	}
	//
	if (g_GameMode == RunGameMode::MODE_STORY)
	{
		int curscene = ResDef::getInstance()->g_ConfigStruct.CurrentArea - 1;
		int curlevel = ResDef::getInstance()->g_ConfigStruct.CurrentLevel - 1;
		GameLevel* ldata = LevelManager::Instance()->m_Areas[curscene]->GetGameLevel(curlevel);
		if (ldata != nullptr)
		{
			SetPlayersType(GameRoleType::GameRoleType_ARSEHOLE, (GameRoleType)(ldata->getEnemyRoleType()));
		}    
	}
	InitPlayers();
	SetAIEnable(UseAI);
	//
	m_AI->body = m_PlayerB;
	m_AI->enemy = m_PlayerA;
	m_AI->road = m_Track;
	//
	if (m_PlayerA != nullptr)
	{
		m_PlayerA->restart();
	}
	if (m_PlayerB != nullptr)
	{
		m_PlayerB->restart();
	}
	if (m_AI != nullptr)
	{
		m_AI->restart();
	}


	//
	EffectManager::Instance()->RemoveAllParticleEffects();
	//

	//if (ResDef.g_ConfigStruct.EnableAudio != 0)
	//{
	//    SimpleAudioEngine.sharedEngine().stopBackgroundMusic();
	//}
	SoundManager::Instance()->StopMusic();

	m_LevelUpCountdown = m_EveryLevelUpMax;
	m_GameLevel = 0;
}

void GameScene::onEnter()
{
	Layer::onEnter();
	scheduleUpdate();
}

void GameScene::onExit()
{
	unscheduleUpdate();
	Layer::onExit();
}

int GameScene::GetSceneIndex() 
{ 
	return m_SceneIndex; 
}

int GameScene::GetPlayerNum()
{
	if (UseAI) 
		return 1; 
	else 
		return 2;
}

void GameScene::SetPlayersType(GameRoleType TypeA, GameRoleType TypeB)
{
	PlayerAType = TypeA;
	PlayerBType = TypeB;
}

void GameScene::SetAIEnable(bool b)
{
	UseAI = b;
	m_AI->SetEnable(UseAI);
}

void GameScene::callbackShowLabel()
{
	ShowLabelAnimation();
}

void GameScene::ShowLabelAnimation()
{
	ShowLabel = true;
}

void GameScene::callbackShowEndStoryUI()
{
	Director::getInstance()->replaceScene(StoryEndUI::createScene());
}
void GameScene::randomCreateCloud()
{
	int rot = (int)(CCRANDOM_0_1() * 20.0f);
	m_Track->CreateTrap(rot*13.0f,TrapType::TRAP_CLOUD);
}

void GameScene::randomCreateRedCactus()
{
	int rot = (int)(CCRANDOM_0_1() * 20.0f);
	m_Track->CreateTrap(rot * 13.0f, TrapType::TRAP_REDCACTUS);
}

void GameScene::randomCreateStorm()
{
	int rot = (int)(CCRANDOM_0_1() * 20.0f);
	m_Track->CreateTrap(rot * 13.0f, TrapType::TRAP_STORM);
}

void GameScene::randomCreateCoin()
{
	int rot = (int)(CCRANDOM_0_1() * 45.0f);
	m_Track->CreateItem(rot * 8.0f, ItemType::Item_Coin);
}

void GameScene::createAllCoinEdge()
{
	m_Track->CreateCoinEdge();
}

void GameScene::createAllCoin()
{
	m_Track->CreateAllCoin();
}

void GameScene::QuitGame(Ref* pSender)
{
	SoundManager::Instance()->StopMusic();

	Director::getInstance()->replaceScene(LogoUI::createScene());   
}