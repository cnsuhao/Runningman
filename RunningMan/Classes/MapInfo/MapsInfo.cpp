#include "MapsInfo.h"
#include "Player/PlayerManager.h"
#include "Player/PlayerStatus.h"
#include "Scene/GameScene.h"
#include "Scene/Track.h"
#include "Player/Player.h"


void LevelData::Init(LevelRuleType rule, int overLaps, int collectNum, bool isboss, int roleType, int sceneTexID)
{
	m_RuleType = rule;
	m_LevelRule.SetOverLaps(overLaps);
	m_LevelRule.SetCollectNum(collectNum);
	m_bCreateCoin = false;
	m_bRandomCoin = false;
	m_ReadyCreateCoinNum = 0;
	m_MapTexID = 1;
	m_LimitTime = 0.0f;
	m_EnemyRoleType = roleType;
	m_bIsBoss = isboss;

	m_MapTexID = sceneTexID;

	switch(m_RuleType)
	{
	case LevelRuleType::RULE_COLLECT_ALLCOIN:
		{
			m_bCreateCoin = true;
			m_ReadyCreateCoinNum = 100;

		}
		break;
	case LevelRuleType::RULE_COLLECT_COIN:
		{
			m_bCreateCoin = true;
			m_bRandomCoin = true;
			m_ReadyCreateCoinNum = 10;
			m_LimitTime = 60.0f;

		}
		break;
	}
}

bool LevelData::IsMatchOver()
{
	Player* pPlayA = PlayerManager::Instance()->GetPlayerA();
	Player* pPlayB = PlayerManager::Instance()->GetPlayerB();

	switch (m_RuleType)
	{
	case LevelRuleType::RULE_CATCH_RIVALS:
		{
			float AtotalAngle = pPlayA->getTotalRunAngle();
			float BtotalAngle = pPlayB->getTotalRunAngle();
			if ((AtotalAngle - BtotalAngle) > 180.0f)
			{
				//A追上了B
				pPlayA->win();
				pPlayB->lose();
				return true;
			}
			else if ((BtotalAngle - AtotalAngle) > 180.0f)
			{
				//B追上了A
				pPlayA->lose();
				pPlayB->win();
				return true;
			}
		}
		break;
	case LevelRuleType::RULE_OVER_LAPS:
		{
			float lap = (float)m_LevelRule.GetOverLaps();
			float AtotalAngle = pPlayA->getTotalRunAngle();
			float BtotalAngle = pPlayB->getTotalRunAngle();

			if ((AtotalAngle - BtotalAngle) > 180.0f + 360.0f * lap)
			{
				//A追上了B
				pPlayA->win();
				pPlayB->lose();
				return true;
			}
			else if ((BtotalAngle - AtotalAngle) > 180.0f + 360.0f * lap)
			{
				//B追上了A
				pPlayA->lose();
				pPlayB->win();
				return true;
			}
		}
		break;
	case LevelRuleType::RULE_CAREFULLY_TRAP:
		{
			float AtotalAngle = pPlayA->getTotalRunAngle();
			float BtotalAngle = pPlayB->getTotalRunAngle();

			if (pPlayA->m_FSM->GetCurPlayerStatus() == Player_Fall::Instance() ||
				pPlayA->m_FSM->GetCurPlayerStatus() == Player_Electric::Instance() )
			{
				pPlayA->lose();
				pPlayB->win();
				return true;
			}
			else if (pPlayB->m_FSM->GetCurPlayerStatus() == Player_Fall::Instance() ||
				pPlayB->m_FSM->GetCurPlayerStatus() == Player_Electric::Instance())
			{
				pPlayA->win();
				pPlayB->lose();
				return true;
			}
			else if ((AtotalAngle - BtotalAngle) > 180.0f)
			{
				//A追上了B
				pPlayA->win();
				pPlayB->lose();
				return true;
			}
			else if ((BtotalAngle - AtotalAngle) > 180.0f)
			{
				//B追上了A
				pPlayA->lose();
				pPlayB->win();
				return true;
			}
		}
		break;
	case LevelRuleType::RULE_COLLECT_COIN:
		{
			if (m_LimitTime <= 0.0f)
			{
				if (pPlayA->GetCollectCoin() > pPlayB->GetCollectCoin())
				{
					pPlayA->win();
					pPlayB->lose();
					return true;
				}
				else if (pPlayB->GetCollectCoin() > pPlayA->GetCollectCoin())
				{
					pPlayA->lose();
					pPlayB->win();
					return true;
				}
				else
				{
					pPlayA->lose();
					pPlayB->lose();
					return true;
				}
			}                        
		}
		break;
	case LevelRuleType::RULE_COLLECT_ALLCOIN:
		{
			cocos2d::Scene* pRunningScene = cocos2d::Director::getInstance()->getRunningScene();
			if (pRunningScene != nullptr)
			{
				cocos2d::Node* pLayer = pRunningScene->getChildByTag(GameScene::LayerTag);
				GameScene* pGameLayer = (GameScene*)pLayer;
				if (pGameLayer != nullptr)
				{
					if (pGameLayer->m_Track->getAppearCoin() == 0)
					{
						if (pPlayA->GetCollectCoin() > pPlayB->GetCollectCoin())
						{
							pPlayA->win();
							pPlayB->lose();
							return true;
						}
						else if (pPlayB->GetCollectCoin() > pPlayA->GetCollectCoin())
						{
							pPlayA->lose();
							pPlayB->win();
							return true;
						}
						else
						{
							pPlayA->lose();
							pPlayB->lose();
							return true;
						}
					}
				}
			}
		}
		break;
	}
	return false;
}

//----------------------------------------------------
MapsInfo* MapsInfo::m_Instance = nullptr;

MapsInfo::MapsInfo(void)
{
}


MapsInfo::~MapsInfo(void)
{
}

MapsInfo* MapsInfo::GetInstance()
{
	if (m_Instance == nullptr)
	{
		m_Instance = new MapsInfo();
	}

	return m_Instance;
}

void MapsInfo::FillInfo()
{
	MapData*   Scene_1 = new MapData();
	{
		cocos2d::Vec2 pos;
		Scene_1->LevelNum = 6;
		//Scene_1.LevelDatas = new List<LevelData>(Scene_1.LevelNum);
		//
		LevelData* data;
		pos = cocos2d::Vec2(564,480 - 287);
		data = new LevelData();
		data->levelPoint = pos;
		data->Init(LevelRuleType::RULE_CATCH_RIVALS, 0, 0, false, GameRoleType::GameRoleType_MUMMY, 1);
		Scene_1->LevelDatas.push_back(data);
		//Scene_1.LevelPoints.Add(pos);
		pos = cocos2d::Vec2(493,480 - 272);
		//-------------------------------
		data = new LevelData();
		data->levelPoint = pos;
		data->Init(LevelRuleType::RULE_OVER_LAPS, 2, 0, false, GameRoleType::GameRoleType_MUMMY, 1);
		Scene_1->LevelDatas.push_back(data);
		//Scene_1.LevelPoints.Add(pos);
		pos = cocos2d::Vec2(455,480 - 195);
		//-------------------------------
		data = new LevelData();		
		data->levelPoint = pos;
		data->Init(LevelRuleType::RULE_CAREFULLY_TRAP, 0, 0, true, GameRoleType::GameRoleType_MUMMY, 1);
		Scene_1->LevelDatas.push_back(data);
		//Scene_1.LevelPoints.Add(pos);
		pos = cocos2d::Vec2(475,480 - 138);
		data = new LevelData();
		data->levelPoint = pos;
		data->Init(LevelRuleType::RULE_CATCH_RIVALS, 0, 0, false, GameRoleType::GameRoleType_PHARAOH, 2);
		Scene_1->LevelDatas.push_back(data);
		//Scene_1.LevelPoints.Add(pos);
		pos = cocos2d::Vec2(492, 480 - 145);
		data = new LevelData();
		data->levelPoint = pos;
		data->Init(LevelRuleType::RULE_COLLECT_ALLCOIN, 0, 0, false, GameRoleType::GameRoleType_PHARAOH, 2);
		Scene_1->LevelDatas.push_back(data);
		//Scene_1.LevelPoints.Add(pos);
		pos = cocos2d::Vec2(492, 480 - 125);
		data = new LevelData();
		data->levelPoint = pos;
		data->Init(LevelRuleType::RULE_COLLECT_COIN, 0, 0, true, GameRoleType::GameRoleType_PHARAOH, 2);
		Scene_1->LevelDatas.push_back(data);
		//
	}
	//
	SceneDataPool.push_back(Scene_1);

	//-------------------------------------------------
	//vs
	VsSceneData = new MapData(); 
	cocos2d::Vec2 vspos;
	VsSceneData->LevelNum = 1;
	LevelData* vsdata;
	vspos = cocos2d::Vec2(564, 480 - 287);
	vsdata = new LevelData();
	vsdata->levelPoint = vspos;
	vsdata->Init(LevelRuleType::RULE_COLLECT_COIN, 1, 0, false, GameRoleType::GameRoleType_ARSEHOLE, 1);
	VsSceneData->LevelDatas.push_back(vsdata);
}